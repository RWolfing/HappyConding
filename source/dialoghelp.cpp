/**
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */

#include "dialoghelp.h"
#include "ui_dialoghelp.h"
#include <QFile>


/**
 * Constructs the DialogHelp the given parent.
 * Sets up the Dialog and reads the readme.html file into the
 * textbrowser.
 *
 * @brief DialogHelp::DialogHelp
 * @param parent
 */
DialogHelp::DialogHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHelp)
{
    ui->setupUi(this);

   QFile file("readme.html");

   if (file.open(QFile::ReadOnly))
   {
     ui->textBrowser->setHtml(file.readAll());
     file.close();
   }
}

/**
 * Deconstructs the Dialog.
 *
 * @brief DialogHelp::~DialogHelp
 */
DialogHelp::~DialogHelp()
{
    delete ui;
}
