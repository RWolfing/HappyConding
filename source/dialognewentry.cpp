/**
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */

#include "dialognewentry.h"
#include "ui_dialognewentry.h"
#include <QDate>
#include <QMessageBox>
#include <QSqlQuery>
#include <QString>
#include <QSqlError>


/**
 * Constructs the Dialog with the given parent.
 * Sets up the Date and Language/Pattern-Options
 *
 * @brief DialogNewEntry::DialogNewEntry
 * @param parent
 */
DialogNewEntry::DialogNewEntry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewEntry)
{
    ui->setupUi(this);

    //Date
    currentDate = QDate::currentDate();
    ui->lblDate->setText(currentDate.toString());

    setPatternOptions();
    setLanguageOptions();
}


/**
 * Deconstructs the Dialog
 *
 * @brief DialogNewEntry::~DialogNewEntry
 */
DialogNewEntry::~DialogNewEntry()
{
    delete ui;
}

/**
 * Saves all filled fields as an entry to the database
 *
 * @brief DialogNewEntry::on_bttnSpeichern_clicked
 */
void DialogNewEntry::on_bttnSpeichern_clicked()
{

    QString invalidText = ("background-color: red, opacity: 0.5");
    QString validText = "background-color: white";

    QString nameEntry = ui->lEditEntryName->text();
    QString nameAuthor = ui->lEditAuthor->text();
    QString language = ui->cBoxLanguage->currentText();
    QString system = ui->cBoxSystem->currentText();
    QString pattern = ui->cBoxPattern->currentText();
    QString description = ui->pTEditDescription->toPlainText();
    QString code = ui ->pTEditCode->toPlainText();
    QString date = currentDate.toString("yyyy-MM-dd");

    if(nameEntry.isEmpty())
    {
        ui->lEditEntryName->setStyleSheet(invalidText);
    }
    else
    {
        ui->lEditEntryName->setStyleSheet(validText);
    }


    QString queryString = QString("INSERT INTO Entries"
                        "(EntryName, EntryDate, AutorName , EntryCode , Pattern , System , CodeLanguage , CodeDescription , Sources )"
                        " VALUES ('%1','%2','%3','%4','%5','%6','%7','%8',%9);")
                        .arg(nameEntry).arg(date).arg(nameAuthor).arg(code).arg(pattern).arg(system).arg(language).arg(description).arg(1);

     QSqlQuery query;
     query.prepare(queryString);

     if(!query.exec())
     {
      QMessageBox::critical(0,"DatabaseError",
                            "Eintrag konnte nicht gespeicher werden... "
                            + query.lastError().text());
      return;
     }
     this->close();
}

/**
 * Retrieves all patterns from the database and adds them to the
 * options.
 *
 * @brief DialogNewEntry::setPatternOptions
 */
void DialogNewEntry::setPatternOptions()
{
    QString queryStatment = QString("SELECT Pattern FROM Patterns");

    QSqlQuery query;
    query.prepare(queryStatment);

    if(!query.exec())
    {
        QMessageBox::critical(0,"DatabaseError", "Pattern konnten nicht abgerufen werden..."
                              + query.lastError().text());
        return;
    }

    if(query.first())
    {
        do
        {
            QString pattern = query.value(0).toString();
            ui->cBoxPattern->addItem(pattern, pattern);
        }while(query.next());
    }

}

/**
 * Retrieves all languages from the database and adds them to the
 * options.
 *
 * @brief DialogNewEntry::setLanguageOptions
 */
void DialogNewEntry::setLanguageOptions()
{
    QString queryStatment = QString("SELECT Language FROM Languages");

    QSqlQuery query;
    query.prepare(queryStatment);

    if(!query.exec())
    {
        QMessageBox::critical(0,"DatabaseError", "Sprachen konnten nicht abgerufen werden..."
                              +query.lastError().text());
        return;
    }

    if(query.first())
    {
        do
        {
            QString language = query.value(0).toString();
            ui->cBoxLanguage->addItem(language, language);
        }while(query.next());
    }

}
