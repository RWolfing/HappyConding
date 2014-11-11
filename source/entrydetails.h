#ifndef ENTRYDETAILS_H
#define ENTRYDETAILS_H

#include <QDialog>
#include "entryentity.h"

namespace Ui {
class EntryDetails;
}

/**
 * @brief The EntryDetails class
 *
 *  This class represents a QDialog to show information about one entry.
 *
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */
class EntryDetails : public QDialog
{
    Q_OBJECT

public:
    explicit EntryDetails(EntryEntity entity, QWidget *parent = 0);
    ~EntryDetails();

private slots:
    void on_bttnDelete_clicked();

private:
    Ui::EntryDetails *ui;

    EntryEntity entity;
};

#endif // ENTRYDETAILS_H
