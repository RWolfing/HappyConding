#ifndef DIALOGHELP_H
#define DIALOGHELP_H

#include <QDialog>

namespace Ui {
class DialogHelp;
}

/**
 * @brief The DialogHelp class
 *
 * This class represents the Helpdialog.
 *
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */
class DialogHelp : public QDialog
{
    Q_OBJECT

public:
    explicit DialogHelp(QWidget *parent = 0);
    ~DialogHelp();

private:
    Ui::DialogHelp *ui;
};

#endif // DIALOGHELP_H
