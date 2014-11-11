#ifndef ENTRYWIDGET_H
#define ENTRYWIDGET_H

#include <QWidget>
#include "entryentity.h"

namespace Ui {
class EntryWidget;
}


/**
 * @brief The EntryWidget class
 *
 * This class represents a Qwidget used to visualize one single entry in the MainWindow.
 *
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */
class EntryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EntryWidget(QWidget *parent = 0, QString date = "Date", QString name = "Name", QString pattern = "Pattern", QString lang = "Language");
    EntryWidget(EntryEntity entity, QWidget *parent = 0);

    ~EntryWidget();

protected:
   void paintEvent(QPaintEvent *);
   void mouseDoubleClickEvent(QMouseEvent *event);
   void mousePressEvent(QMouseEvent *event);
   void mouseReleaseEvent(QMouseEvent *event);
   void mouseMoveEvent(QMouseEvent *event);

   EntryEntity getEntity();
   void setEntryEntity(EntryEntity entity);


private:
    Ui::EntryWidget *ui;

    EntryEntity entity;
    QColor langColor;
    QColor patternColor;

    void setupColor();

};

#endif // ENTRYWIDGET_H
