/**
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */

#include "dialogsettings.h"
#include "ui_dialogsettings.h"
#include "dialogsimpleentry.h"
#include "qdebug.h"
#include "mainwindow.h"
#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QListWidgetItem>
#include <QBrush>
#include <QColor>
#include <entryentity.h>
#include <QTime>
#include <QMessageBox>

/**
 * Constructs the dialog. Retrieves all languages and patterns from
 * the database and adds them to the dialog.
 *
 * @brief DialogSettings::DialogSettings
 * @param parent
 */
DialogSettings::DialogSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSettings)
{
    ui->setupUi(this);

    //Get Languages
    QSqlQuery query;
    if(query.exec("SELECT Language, Color FROM Languages"))
    {
        while(query.next())
        {
            QString language = query.value(0).toString();
            QString colorHex = query.value(1).toString();

            QColor color;
            color.setNamedColor(colorHex);

            QBrush brush(color);
            QListWidgetItem *widgetItem = new QListWidgetItem();
            widgetItem->setBackground(brush);
            widgetItem->setText(language);
            widgetItem->setForeground(QBrush(MainWindow::calculateTextColor(color)));

            ui->listWidgetLang->addItem(widgetItem);
        }
    }
    else
    {
        QMessageBox::critical(0, "DatabaseError", "Sprachen konnten nicht geladen werden... " + query.lastError().text());
    }

    //Get Pattern
    if(query.exec("SELECT Pattern, Color FROM Patterns"))
    {
        while(query.next())
        {
            QString pattern = query.value(0).toString();
            QString colorHex = query.value(1).toString();

            QColor color;
            color.setNamedColor(colorHex);

            QBrush brush(color);
            QListWidgetItem *widgetItem = new QListWidgetItem();
            widgetItem->setBackground(brush);
            widgetItem->setText(pattern);
            widgetItem->setForeground(QBrush(MainWindow::calculateTextColor(color)));
            ui->listWidgetPattern->addItem(widgetItem);
        }
    }
    else
    {
         QMessageBox::critical(0, "DatabaseError", "Pattern konnten nicht geladen werden... " + query.lastError().text());
    }
}


/**
 * Deconstructs the dialog
 *
 * @brief DialogSettings::~DialogSettings
 */
DialogSettings::~DialogSettings()
{
    delete ui;
}

/**
 * Opens the dialog to add a pattern and if submitted adds the pattern
 * to the QListWidget.
 *
 * @brief DialogSettings::on_bttnAddPattern_clicked
 */
void DialogSettings::on_bttnAddPattern_clicked()
{
    DialogSimpleEntry simpleDialog(this, "Pattern");
    if(simpleDialog.exec() == QDialog::Accepted)
    {
       QString text = simpleDialog.getTextFieldContent();
       if(!text.isEmpty())
       {
       QBrush brush(simpleDialog.getColor());
       QListWidgetItem *widgetItem = new QListWidgetItem();
       widgetItem->setBackground(brush);
       widgetItem->setText(text);
       widgetItem->setForeground(QBrush(MainWindow::calculateTextColor(simpleDialog.getColor())));

       ui->listWidgetPattern->addItem(widgetItem);
       }
    }
}

/**
 * Opens the dialog to add a language and if submitted adds the language
 * to the QListWidget.
 *
 * @brief DialogSettings::on_bttnAddPattern_clicked
 */
void DialogSettings::on_bttnAddLang_clicked()
{
    DialogSimpleEntry simpleDialog(this, "Sprache");
    if(simpleDialog.exec() == QDialog::Accepted)
    {
       QString text = simpleDialog.getTextFieldContent();
       if(!text.isEmpty())
       {

       QBrush brush(simpleDialog.getColor());
       QListWidgetItem *widgetItem = new QListWidgetItem();
       widgetItem->setBackground(brush);
       widgetItem->setText(text);
       widgetItem->setForeground(QBrush(MainWindow::calculateTextColor(simpleDialog.getColor())));

       ui->listWidgetLang->addItem(widgetItem);
       }
    }

}

/**
 * Saves all items in the QListWidget to the database.
 *
 * TODO All entries in the table are first deleted and then all items are saved.
 * Not the most efficient way... This has to be reworked.
 *
 * @brief DialogSettings::on_bttnSave_clicked
 */
void DialogSettings::on_bttnSave_clicked()
{
    QListWidgetItem *item;

    QSqlQuery query;

    //Sprachen
    query.prepare("DELETE FROM Languages;");
    if(!query.exec())
        qDebug() << "Konnte Sprachen nicht löschen: " << query.lastError();

    QString finalQuery = "";

    if  (ui->listWidgetLang->count() > 0) {
        for(int i = 0; i < ui->listWidgetLang->count(); i++)
        {
              item = ui->listWidgetLang->item(i);

              if(i == 0)
              {

                  QString simpleStart = QString("INSERT OR IGNORE INTO Languages SELECT '%1' AS ID, '%2' AS Language, '%3' AS COLOR ")
                                                 .arg(0).arg(item->text()).arg(item->backgroundColor().name(QColor::HexArgb));
                  finalQuery.append(simpleStart);
              }
              else
              {
                  QString queryStatement = QString(" UNION SELECT '%1' , '%2' , '%3' ")
                                                    .arg(i).arg(item->text()).arg(item->backgroundColor().name(QColor::HexArgb));
                  finalQuery.append(queryStatement);

              }
        }
        finalQuery.append(";");

        if(!query.prepare(finalQuery))
        {
            QMessageBox::critical(0, "Error", "Fehler beim Speichern (Prepare)... " + query.lastError().text());
            return;
        }

        if(!query.exec())
        {
            QMessageBox::critical(0, "Error", "Fehler beim Speichern langsuag(Exec)... " + query.lastError().text());
            return;
        }
    }



    //Pattern
    query.prepare("DELETE FROM Patterns;");

    if(!query.exec())
        qDebug() << "Konnte Pattern nicht löschen: " << query.lastError();

    if (ui->listWidgetPattern->count() > 0) {
        for(int i = 0; i < ui->listWidgetPattern->count(); i++)
        {
              item = ui->listWidgetPattern->item(i);

              QString color = item->backgroundColor().name(QColor::HexArgb);
              QString queryStatement = QString("INSERT OR IGNORE INTO Patterns(Pattern, Color) "
                                               "VALUES('%1', '%2');")
                                              .arg(item->text()).arg(color);
              if(!query.prepare(queryStatement))
              {
                  QMessageBox::critical(0, "Error", "Fehler beim Speichern (Prepare)... " + query.lastError().text());
                  return;
              }

              if(!query.exec())
              {
                  QMessageBox::critical(0, "Error", "Fehler beim Speichern (Exec)... " + query.lastError().text());
                  return;
              }

        }
    }

    this->close();
}

/**
 * Closes the dialog.
 *
 * @brief DialogSettings::on_bttnClose_clicked
 */
void DialogSettings::on_bttnClose_clicked()
{
    this->close();
}

/**
 * Removes all selected patterns from the QListWidget.
 *
 * @brief DialogSettings::on_bttnRemovePattern_clicked
 */
void DialogSettings::on_bttnRemovePattern_clicked()
{
    qDeleteAll(ui->listWidgetPattern->selectedItems());

}

/**
 * Removes all selected languages from the QListWidget.
 *
 * @brief DialogSettings::on_bttnRemoveLanguage_clicked
 */
void DialogSettings::on_bttnRemoveLanguage_clicked()
{
    qDeleteAll(ui->listWidgetLang->selectedItems());
}
