/**
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */

#include "dialogsimpleentry.h"
#include "ui_dialogsimpleentry.h"
#include <QString>
#include <QColorDialog>

/**
 * Constructs the dialog with the given parent and lblName. Sets the caption to the given lblName
 * and the default color.
 *
 * @brief DialogSimpleEntry::DialogSimpleEntry
 * @param parent
 * @param lblName
 */
DialogSimpleEntry::DialogSimpleEntry(QWidget *parent, QString lblName) :
    QDialog(parent),
    ui(new Ui::DialogSimpleEntry)
{
    ui->setupUi(this);
    ui->lblFieldTItle->setText(lblName);

    //Set default white
    color = QColor();
    color.setRgb(255,255,255,255);
}

/**
 * Deconstructs the dialog
 *
 * @brief DialogSimpleEntry::~DialogSimpleEntry
 */
DialogSimpleEntry::~DialogSimpleEntry()
{
    delete ui;
}

/**
 * Returns the content of the QLineEdit.
 *
 * @brief DialogSimpleEntry::getTextFieldContent
 * @return  content of the textfield
 */
QString DialogSimpleEntry::getTextFieldContent()
{
  return ui->lEdit->text();
}

/**
 * Opens up a QColorDialog and sets the background color of the QPushButton to the selected color.
 *
 * @brief DialogSimpleEntry::on_bttnPickColor_clicked
 */
void DialogSimpleEntry::on_bttnPickColor_clicked()
{
    QColorDialog dialog(this);
    if(dialog.exec() == 1)
    {
        color = dialog.selectedColor();
        QString style("background: #"
                      + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                      + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                      + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";");
        ui->bttnPickColor->setStyleSheet(style);
        ui->bttnPickColor->update();
    }
}

/**
 * Returns the picked background color.
 *
 * @brief DialogSimpleEntry::getColor
 * @return color
 */
QColor DialogSimpleEntry::getColor(){
    return color;
}
