/**
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */

#include "entrydetails.h"
#include "ui_entrydetails.h"
#include "entryentity.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QMessageBox>

/**
 * Constructs the dialog. All information is retrieved from the given EntryEntity object and set as content
 * of the appropriate labels.
 *
 * @brief EntryDetails::EntryDetails
 * @param entity
 * @param parent
 */
EntryDetails::EntryDetails(EntryEntity entity, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntryDetails)
{
    ui->setupUi(this);
    this->entity = entity;

    ui->lblName->setText(this->entity.getEntryName());
    ui->lblDate->setText(this->entity.getEntryDate());
    ui->lblAuthor->setText("@author " + this->entity.getAuthorName());
    ui->lblLang->setText(this->entity.getLanguage());
    ui->lblPattern->setText(this->entity.getPattern());
    ui->lblSystem->setText(entity.getSystem());

    ui->textBrowserCode->setPlainText(this->entity.getEntryCode());
    ui->textBrowser->setText(this->entity.getDescription());
}

/**
 * Deconstructs the dialog.
 *
 * @brief EntryDetails::~EntryDetails
 */
EntryDetails::~EntryDetails()
{
    delete ui;
}

/**
 * Deletes the entry in the database and closes the dialog.
 *
 * @brief EntryDetails::on_bttnDelete_clicked
 */
void EntryDetails::on_bttnDelete_clicked()
{
    QString queryStatement = QString("DELETE FROM Entries "
                                     "WHERE ID = ");
    queryStatement.append(QString::number(this->entity.getEntryId()));

    QSqlQuery query;
    query.prepare(queryStatement);

    if(!query.exec())
    {
        QMessageBox::critical(0, "Error", "Eintrag konnte nicht gelöscht werden... " + query.lastError().text());
        return;
    }   
    this->close();
}
