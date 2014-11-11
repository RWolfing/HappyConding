/**
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialognewentry.h"
#include "dialogsettings.h"
#include "flowlayout.h"
#include "simplecriteria.h"
#include "dialogsearchcriteria.h"
#include "entrywidget.h"
#include "entryentity.h"
#include "dialoghelp.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QMultiMap>
#include <QString>

#include <QMessageBox>
#include <QColor>


/**
 * Constructs the mainwindow of the application.
 * Buttons are getting connected to their appropriate slots.
 * Everything necessary for visualizing the SimpleCriteria is being set up.
 *
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->bttnNewEntry, SIGNAL(clicked()), this, SLOT(open_NewEntryDialog()));
    connect(ui->actionEinstellungen, SIGNAL(triggered()), this,SLOT(open_SettingsDialog()));
    connect(ui->actionHilfe, SIGNAL(triggered()), this, SLOT(open_HelpDialog()));

    flowLayoutCriteria = new FlowLayout;
    flowLayoutCriteria->setObjectName("FlowLayoutCriteria");
    flowLayoutCriteria->setContentsMargins(10, 15, 10 , 10);
    flowLayoutEntries = new FlowLayout;
    ui->gBoxSearchCriteria->setLayout(flowLayoutCriteria);
    ui->scrollAreaEntries->widget()->setLayout(flowLayoutEntries);

    criteria = new QMultiMap<QString, QString>();
}


/**
 * Deconstructs the MainWindow.
 *
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete criteria;
    delete flowLayoutCriteria;
    delete flowLayoutEntries;
    delete ui;
}

/**
 * Opens a DialogNewEntry to create a new entry.
 *
 * @brief MainWindow::open_NewEntryDialog
 */
void MainWindow::open_NewEntryDialog()
{
    DialogNewEntry dialog(this);
    dialog.exec();
}

/**
 * Opens a DialogSettings for the settings.
 *
 * @brief MainWindow::open_SettingsDialog
 */
void MainWindow::open_SettingsDialog()
{
    DialogSettings dialog(this);
    dialog.exec();

}

/**
 * Opens the DialogHelp.
 *
 * @brief MainWindow::open_HelpDialog
 */
void MainWindow::open_HelpDialog()
{
    DialogHelp dialog(this);
    dialog.exec();
}


/**
 * Executes a QSqlQuery to search for entries on the database with the in the MainWindow set criterias.
 *
 * @brief MainWindow::on_bttnSearch_clicked
 */
void MainWindow::on_bttnSearch_clicked()
{
    doSearch();
}

/**
 * Opens the DialogSearchCriteria to customize the search criteria.
 * The finished slot of the DialogSearchCriteria gets connected to the closed_CriteriaDialog() in order
 * to save any criterias.
 *
 * @brief MainWindow::on_bttnCustomize_clicked
 */
void MainWindow::on_bttnCustomize_clicked()
{
    dialogSearchCriteria = new DialogSearchCriteria(this);
    connect(dialogSearchCriteria, SIGNAL(finished(int)), this, SLOT(closed_CriteriaDialog()));
    dialogSearchCriteria->exec();
}

/**
 * Saves the criteria from the DialogSearchCriteria
 * and executes a QsqlQuery search on the database.
 *
 * @brief MainWindow::closed_CriteriaDialog
 */
void MainWindow::closed_CriteriaDialog(){

    if(dialogSearchCriteria->result() == QDialog::Accepted)
    {
       clearCriteriaFlowLayout();
       criteria = new QMultiMap<QString, QString>(dialogSearchCriteria->getCriteriaMap());

       //EntryName
       if(criteria->contains(DialogSearchCriteria::KEY_NAME_ENTRY()))
       {
       SimpleCriteria *simpCrit = new SimpleCriteria(0, DialogSearchCriteria::KEY_NAME_ENTRY(), criteria);
       flowLayoutCriteria->addWidget(simpCrit);
       }

       //AutorName
       if(criteria->contains(DialogSearchCriteria::KEY_NAME_AUTHOR()))
       {
       SimpleCriteria *simpCrit = new SimpleCriteria(0, DialogSearchCriteria::KEY_NAME_AUTHOR(), criteria);
       flowLayoutCriteria->addWidget(simpCrit);
       }

       //Code
       if(criteria->contains(DialogSearchCriteria::KEY_CODE()))
       {
       SimpleCriteria *simpCrit = new SimpleCriteria(0, DialogSearchCriteria::KEY_CODE(), criteria);
       flowLayoutCriteria->addWidget(simpCrit);
       }

       //Codedescription
       if(criteria->contains(DialogSearchCriteria::KEY_DESCR()))
       {
       SimpleCriteria *simpCrit = new SimpleCriteria(0, DialogSearchCriteria::KEY_DESCR(), criteria);
       flowLayoutCriteria->addWidget(simpCrit);
       }

       //Pattern
       if(criteria->contains(DialogSearchCriteria::KEY_PATTERN()))
       {
       QList<QString> patterns = criteria->values(DialogSearchCriteria::KEY_PATTERN());

       for(int i = 0; i < patterns.size(); i++)
       {
           SimpleCriteria *simpCrit = new SimpleCriteria(0, DialogSearchCriteria::KEY_PATTERN(), criteria);
           simpCrit->setContent(patterns.at(i));
           flowLayoutCriteria->addWidget(simpCrit);
       }
       }

       //Languages
       if(criteria->contains(DialogSearchCriteria::KEY_LANGUAGE()))
       {
       QList<QString> languages = criteria->values(DialogSearchCriteria::KEY_LANGUAGE());
       for(int i = 0; i < languages.size(); i++)
       {
           SimpleCriteria *simpCrit = new SimpleCriteria(0, DialogSearchCriteria::KEY_LANGUAGE(), criteria);
           simpCrit->setContent(languages.at(i));
           flowLayoutCriteria->addWidget(simpCrit);
       }
       }
       doSearch();
    }

    delete dialogSearchCriteria;
}

/**
 * Executes a QSqlQuery to search for entries with the given parameters.
 *
 * @brief MainWindow::doSearch
 */
void MainWindow::doSearch()
{
    clearEntriesFlowLayout();
    QString queryStatement = QString("SELECT * "
                             "FROM Entries "
                             "WHERE EntryName LIKE '%1' "
                             "AND AutorName LIKE '%2' "
                             "AND EntryDate BETWEEN '%3' AND '%4' "
                             "AND EntryCode LIKE '%5' "
                             "AND Pattern %6 "
                             "AND System LIKE '%7' "
                             "AND CodeLanguage %8 "
                             "AND CodeDescription LIKE '%9';");

    QString defValue = "%";
    QString customDefValue = "LIKE '%'"; // Patten und Language brauchen mal wieder ne extra Wurst...
    QString defaultDateFrom = "0000-00-00";
    QString defaultDateTo = "now";

    if(criteria && !criteria->empty())
    {
        //EntryName
        queryStatement = queryStatement.arg(criteria->value(DialogSearchCriteria::KEY_NAME_ENTRY(), defValue));

        //AuthorName
        queryStatement = queryStatement.arg(criteria->value(DialogSearchCriteria::KEY_NAME_AUTHOR(), defValue));

        //Date
        if(!criteria->values(DialogSearchCriteria::KEY_DATE()).isEmpty())
        {
        queryStatement = queryStatement.arg(criteria->values(DialogSearchCriteria::KEY_DATE()).first());
        queryStatement = queryStatement.arg(criteria->values(DialogSearchCriteria::KEY_DATE()).last());
        }
        else
        {
        queryStatement =  queryStatement.arg(defaultDateFrom);
        queryStatement = queryStatement.arg(defaultDateTo);
        }

        //Code
        queryStatement = queryStatement.arg(criteria->value(DialogSearchCriteria::KEY_CODE(), defValue));

        //Pattern
        if(!criteria->values(DialogSearchCriteria::KEY_PATTERN()).isEmpty())
        {
            QString patternQuery = "IN (";
            QList<QString> patternList = criteria->values(DialogSearchCriteria::KEY_PATTERN());

            for(int i = 0; i < patternList.size()-1; i++)
            {
                patternQuery.append("'" + patternList.at(i) + "' , ");
            }
            patternQuery.append("'" + patternList.last() + "') ");
            queryStatement =  queryStatement.arg(patternQuery);
        }
        else
        {
            queryStatement = queryStatement.arg(customDefValue);
        }

        //System
        queryStatement = queryStatement.arg(defValue);

        //Languages
        if(!criteria->values(DialogSearchCriteria::KEY_LANGUAGE()).isEmpty())
        {
            QString langQuery = "IN (";
            QList<QString> langList = criteria->values(DialogSearchCriteria::KEY_LANGUAGE());

            for(int i = 0; i < langList.size()-1; i++)
            {
                langQuery.append("'" + langList.at(i) + "' , ");
            }

            langQuery.append("'" + langList.last() + "') ");
            queryStatement = queryStatement.arg(langQuery);
        }
        else
        {
            queryStatement = queryStatement.arg(customDefValue);
        }

        //Description
        queryStatement = queryStatement.arg(criteria->value(DialogSearchCriteria::KEY_DESCR(), defValue));
    }

    else
    {
        queryStatement = queryStatement
                .arg(defValue)
                .arg(defValue)
                .arg(defaultDateFrom)
                .arg(defaultDateTo)
                .arg(defValue)
                .arg(customDefValue)
                .arg(defValue)
                .arg(customDefValue)
                .arg(defValue);
    }

    //Exec Search
    QSqlQuery query;
    query.prepare(queryStatement);

    if(!query.exec())
    {
        QMessageBox::critical(0, "DatabaseError", "Fehler beim Ausführen der Suche: " + query.lastError().text());
        return;
    }

    int idFieldNo = query.record().indexOf("ID");
    int nameFieldNo = query.record().indexOf("EntryName");
    int dateFieldNo = query.record().indexOf("EntryDate");
    int authorNameFieldNo = query.record().indexOf("AutorName");
    int codeFieldNo = query.record().indexOf("EntryCode");
    int patternFieldNo = query.record().indexOf("Pattern");
    int systemFieldNo = query.record().indexOf("System");
    int codeLangFieldNo = query.record().indexOf("CodeLanguage");
    int codeDescrFieldNo = query.record().indexOf("CodeDescription");
    int sourcesFieldNo = query.record().indexOf("Sources");


    while (query.next()) {    

         //Setup Entity
         EntryEntity entity;
         entity.setEntryId(query.value(idFieldNo).toInt());
         entity.setEntryName(query.value(nameFieldNo).toString());
         entity.setEntryDate(query.value(dateFieldNo).toString());
         entity.setAuthorName(query.value(authorNameFieldNo).toString());
         entity.setEntryCode(query.value(codeFieldNo).toString());
         entity.setPattern(query.value(patternFieldNo).toString());
         entity.setSystem(query.value(systemFieldNo).toString());
         entity.setLanguage(query.value(codeLangFieldNo).toString());
         entity.setDescription(query.value(codeDescrFieldNo).toString());
         entity.setSourceKey(query.value(sourcesFieldNo).toInt());

         EntryWidget *widget = new EntryWidget(entity, 0);
         flowLayoutEntries->addWidget(widget);
    }

}

/**
 * Deletes all SimpleCriteria objects from the FlowLayout.
 *
 * @brief MainWindow::clearCriteriaFlowLayout
 */
void MainWindow::clearCriteriaFlowLayout()
{
       QLayoutItem *item = NULL;
       while ((item = flowLayoutCriteria->takeAt(0)) != 0) {
           delete item->widget();
       }
}

/**
 * Deletes all EntryWidget objects from the FlowLayout.
 *
 * @brief MainWindow::clearEntriesFlowLayout
 */
void MainWindow::clearEntriesFlowLayout()
{
    QLayoutItem *item = NULL;
    while ((item = flowLayoutEntries->takeAt(0)) != 0) {
        delete item->widget();
    }
}


/**
 * Calculates the appropriate textcolor for a given background.
 *
 * @brief MainWindow::calculateTextColor
 * @param background
 * @return textcolor
 */
QColor MainWindow::calculateTextColor(QColor background)
{
    int brightness = background.red() * 0.299 + background.green() * 0.587 + background.blue() * 0.114;
    QColor textColor = QColor(Qt::gray);
    if(brightness < 186)
    {
        textColor.setRgb(255,255,255);
    }
    else
    {
        textColor.setRgb(0,0,0); ;
    }

    return textColor;
}


/**
 * Opens the DialogHelp.
 *
 * @brief MainWindow::on_bttnHelp_clicked
 */
void MainWindow::on_bttnHelp_clicked()
{
    open_HelpDialog();
}
