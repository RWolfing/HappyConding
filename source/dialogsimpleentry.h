#ifndef DIALOGSIMPLEENTRY_H
#define DIALOGSIMPLEENTRY_H

#include <QDialog>
#include <QString>

namespace Ui {
class DialogSimpleEntry;
}

/**
 * @brief The DialogSimpleEntry class
 *
 * This class represents a QDialog to create one pattern or language entry.
 *
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */
class DialogSimpleEntry : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSimpleEntry(QWidget *parent = 0, QString lblName = "Default");
    ~DialogSimpleEntry();

    QString getTextFieldContent();
    QColor getColor();

private slots:
    void on_bttnPickColor_clicked();

private:
    Ui::DialogSimpleEntry *ui;
    QColor color;
};

#endif // DIALOGSIMPLEENTRY_H
