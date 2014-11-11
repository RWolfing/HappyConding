#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

#include <QDialog>

namespace Ui {
class DialogSettings;
}

/**
 * @brief The DialogSettings class
 *
 *  This class represents the QDialog for the settings.
 *
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */
class DialogSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSettings(QWidget *parent = 0);
    ~DialogSettings();

private slots:

    void on_bttnAddPattern_clicked();

    void on_bttnAddLang_clicked();

    void on_bttnSave_clicked();

    void on_bttnClose_clicked();

    void on_bttnRemovePattern_clicked();

    void on_bttnRemoveLanguage_clicked();

private:
    Ui::DialogSettings *ui;

};

#endif // DIALOGSETTINGS_H
