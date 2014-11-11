/**
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */

#include "dialogsearchcriteria.h"
#include "ui_dialogsearchcriteria.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QCheckBox>
#include <QMultiMap>
#include <QList>
#include <QString>
#include <QDate>
#include <QMessageBox>

/**
 * Constructs the dialog. Sets up patterns, languages and the date.
 *
 * @brief DialogSearchCriteria::DialogSearchCriteria
 * @param parent
 */
DialogSearchCriteria::DialogSearchCriteria(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSearchCriteria)
{
    ui->setupUi(this);
    createPatternLayout();
    createLanguageLayout();

    QDate dayZero;
    dayZero.setDate(1,1,1);
    ui->datEditFrom->setDate(dayZero);
    ui->datEditTo->setDate(QDate::currentDate());
}

/**
 * Deconstructs the dialog.
 *
 * @brief DialogSearchCriteria::~DialogSearchCriteria
 */
DialogSearchCriteria::~DialogSearchCriteria()
{
    delete ui;
}

/**
 * Returns the CriteriaMap of the DialogSearchCriteria.
 *
 * @brief DialogSearchCriteria::getCriteriaMap
 * @return CriteriaMap
 */
QMultiMap<QString, QString> DialogSearchCriteria::getCriteriaMap()
{
    return criteriaMap;
}

/**
 * Creates the layout for the patterns after retrieving them
 * from the database.
 *
 * @brief DialogSearchCriteria::createPatternLayout
 */
void DialogSearchCriteria::createPatternLayout()
{
    QSqlQuery query;
    QString queryStatement = "SELECT Pattern FROM Patterns";

    if(!query.exec(queryStatement))
    {
       QMessageBox::critical(0, "DatabaseError" , "Pattern konnten nicht abgerufen werden... " + query.lastError().text());
       return;
    }

    QLayout *widget = ui->scrollAreaContentPattern->layout();
    widget->setObjectName("LayoutPattern");
    while(query.next())
    {
        QCheckBox *checkBox = new QCheckBox();
        checkBox->setText(query.value(0).toString());
        widget->addWidget(checkBox);
    }


       // TODO unfinished code... align elements in rows depending on their count

//    int numberFirstRow;
//    int numberSecondRow;
//    int numberThirdRow;

//    double numberResults = (double) query.size();

//    double afterComma = (numberResults / 3) - ((static_cast<int>(numberResults) / 3));

//    if(afterComma < 0.6)
//    {
//        numberFirstRow = static_cast<int>(numberResults / 3) + 1;
//        numberSecondRow = static_cast<int>(numberResults / 3) + 1 ;
//        numberThirdRow = static_cast<int>(numberResults / 3);
//    }
//    if(afterComma < 0.4)
//    {
//        numberFirstRow = static_cast<int>(numberResults / 3) + 1;
//        numberSecondRow = static_cast<int>(numberResults / 3);
//        numberThirdRow = static_cast<int>(numberResults / 3);
//    }
//    else
//    {
//        numberFirstRow = numberSecondRow = numberThirdRow = numberResults / 3;
//    }
}

/**
 * Creates the layout for the languages after retrieving them
 * from the database.
 *
 * @brief DialogSearchCriteria::createLanguageLayout
 */
void DialogSearchCriteria::createLanguageLayout()
{

    QSqlQuery query;
    QString queryStatement = "SELECT Language FROM Languages";

    if(!query.exec(queryStatement))
    {
       QMessageBox::critical(0, "DatabaseError" , "Sprachen konnten nicht abgerufen werden... " + query.lastError().text());
       return;
    }

    QLayout *widget = ui->scrollAreaContentLanguage->layout();
    while(query.next())
    {
        QCheckBox *checkBox = new QCheckBox();
        checkBox->setText(query.value(0).toString());
        widget->addWidget(checkBox);
    }
}


/**
 * Retrieves all the inserted information, saves it into a HashMap and closes
 * the dialog.
 *
 * @brief DialogSearchCriteria::on_bttnGo_clicked
 */
void DialogSearchCriteria::on_bttnGo_clicked()
{

    QString nameEntry = ui->lEditEntryName->text();
    QString nameAuthor = ui->lEditAuthorName->text();

    if(!nameEntry.isEmpty())
    criteriaMap.insert(DialogSearchCriteria::KEY_NAME_ENTRY(), nameEntry);

    if(!nameAuthor.isEmpty())
    criteriaMap.insert(DialogSearchCriteria::KEY_NAME_AUTHOR(), nameAuthor);

    //Date
    criteriaMap.insert(DialogSearchCriteria::KEY_DATE(), ui->datEditTo->dateTime().toString("yyyy-MM-dd"));
    criteriaMap.insert(DialogSearchCriteria::KEY_DATE(), ui->datEditFrom->dateTime().toString("yyyy-MM-dd"));

    QList<QString> pattern;
    QList<QString> language;

    for(int i = 0; i < ui->scrollAreaContentPattern->children().size(); i++)
    {
        QCheckBox *item = qobject_cast<QCheckBox *> (ui->scrollAreaContentPattern->children().at(i));

        if(item && (item->checkState() == Qt::Checked))
        {
            criteriaMap.insert(DialogSearchCriteria::KEY_PATTERN(), item->text());
        }
    }

    for(int i = 0; i < ui->scrollAreaContentLanguage->children().size(); i++)
    {
        QCheckBox *item = dynamic_cast<QCheckBox*> (ui->scrollAreaContentLanguage->children().at(i));
        if(item && (item->checkState() == Qt::Checked))
        {
            criteriaMap.insert(DialogSearchCriteria::KEY_LANGUAGE(), item->text());
        }
    }


    QString code = ui->tEditCode->document()->toPlainText();
    QString descr = ui->tEditDescr->document()->toPlainText();

    if(!code.isEmpty())
    criteriaMap.insert(DialogSearchCriteria::KEY_CODE(), code);

    if(!descr.isEmpty())
    criteriaMap.insert(DialogSearchCriteria::KEY_DESCR(), descr);

    this->accept();
}
