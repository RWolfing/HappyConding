#ifndef DIALOGNEWENTRY_H
#define DIALOGNEWENTRY_H

#include <QDialog>
#include <QDate>

namespace Ui {
class DialogNewEntry;
}


/**
 * @brief The DialogNewEntry class
 *
 * This class represents the QDialog for creating a new entry.
 *
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */
class DialogNewEntry : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewEntry(QWidget *parent = 0);
    ~DialogNewEntry();

private slots:
    void on_bttnSpeichern_clicked();

private:
    Ui::DialogNewEntry *ui;
    QDate currentDate;

    void setPatternOptions();
    void setLanguageOptions();
};

#endif // DIALOGNEWENTRY_H
