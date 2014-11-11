/**
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */

#include "entrywidget.h"
#include "ui_entrywidget.h"
#include <QString>
#include <QWidget>

#include "entryentity.h"
#include "entrydetails.h"

#include <QPainter>
#include <QColor>
#include <QRect>
#include <QBrush>

#include <QSqlQuery>
#include <QSqlError>

#include <QMessageBox>

#include <mainwindow.h>


/**
 * Constructs the widget. Sets all information from the given parameters.
 * Calculates the textcolor and sets the stylesheet.
 *
 * @brief EntryWidget::EntryWidget
 * @param parent
 * @param date
 * @param name
 * @param pattern
 * @param lang
 */
EntryWidget::EntryWidget(QWidget *parent, QString date, QString name, QString pattern, QString lang) :
    QWidget(parent),
    ui(new Ui::EntryWidget)
{   
    EntryEntity entryEntity;
    this->entity = entryEntity;
    this->entity.setEntryDate(date);
    this->entity.setEntryName(name);
    this->entity.setPattern(pattern);
    this->entity.setLanguage(lang);

    ui->setupUi(this);

    setupColor();
    QString textStyle = QString("color: ");
    QColor textColor = MainWindow::calculateTextColor(this->langColor);
    textStyle.append(textColor.name());

    ui->lblHeader->setText(date);
    ui->lblLang->setText(lang);
    ui->lblName->setText(name);
    ui->lblPattern->setText(pattern);

    this->setStyleSheet(textStyle);
}

/**
 * Constructs the widget. Sets all information from the given EntryEntity and calculates the textcolor.
 *
 * @brief EntryWidget::EntryWidget
 * @param entity
 * @param parent
 */
EntryWidget::EntryWidget(EntryEntity entity, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntryWidget)
{
    this->entity = entity;

    setupColor();
    QString textStyle = QString("color: ");
    QColor textColor = MainWindow::calculateTextColor(this->langColor);
    textStyle.append(textColor.name()).append(";");

    ui->setupUi(this);
    ui->lblHeader->setText(entity.getEntryDate());
    ui->lblLang->setText(entity.getLanguage());
    ui->lblName->setText(entity.getEntryName());
    ui->lblPattern->setText(entity.getPattern());

    this->setStyleSheet(textStyle);
}

EntryWidget::~EntryWidget()
{
    delete ui;
}

/**
 * Retrives the needed color from the database. The background color is the active language color.
 *
 * @brief EntryWidget::setupColor
 */
void EntryWidget::setupColor()
{
    QString langColQuery = QString("SELECT Color FROM Languages WHERE Language LIKE '%1'").arg(this->entity.getLanguage());
    QString patternColQuery = QString("SELECT Color From Patterns Where Pattern LIKE '%1'").arg(this->entity.getPattern());
    this->langColor.setRgb(255, 250, 250);
    this->patternColor.setRgb(255,255,255);

    QSqlQuery query;
    query.prepare(langColQuery);

    if(!query.exec())
    {
        QMessageBox::critical(0, "DatabaseError", "Failed to execute query... " + query.lastError().text());
        return;
    }

    if(query.first())
    {
        this->langColor = QColor(query.value(0).toString());
    }

    query.prepare(patternColQuery);

    if(!query.exec())
    {
        QMessageBox::critical(0, "DatabaseError", "Failed to execute query... " + query.lastError().text());
        return;
    }

    if(query.first())
    {
        this->patternColor = QColor(query.value(0).toString());
    }
}

/**
 * Returns the EntryEntity
 *
 * @brief EntryWidget::getEntity
 * @return entity
 */
EntryEntity EntryWidget::getEntity()
{
    return this->entity;
}


/**
 * Sets the EntryEntity
 *
 * @brief EntryWidget::setEntryEntity
 * @param entity
 */
void EntryWidget::setEntryEntity(EntryEntity entity)
{
    this->entity = entity;
}

/**
 * Paintevent of the widget. This is beeing overwritten in order to set the background color.
 *
 * @brief EntryWidget::paintEvent
 */
void EntryWidget::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   QRect rect(1,1, this->width()-1, this->height()-1);
   QBrush brush;
   brush.setStyle(Qt::SolidPattern);
   brush.setColor(langColor);
   painter.fillRect(rect, brush);
}

/**
 * Doubleclick event for the widget.
 * Opens the EntryDetails dialog.
 *
 * @brief EntryWidget::mouseDoubleClickEvent
 * @param event
 */
void EntryWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    EntryDetails dialog(this->entity, this);
    dialog.exec();
}

/**
 * Event for a mousepress
 *
 * @brief EntryWidget::mousePressEvent
 * @param event
 */
void EntryWidget::mousePressEvent(QMouseEvent *event)
{
}

/**
 * Event for a mouserelease
 *
 * @brief EntryWidget::mouseReleaseEvent
 * @param event
 */
void EntryWidget::mouseReleaseEvent(QMouseEvent *event)
{
}

/**
 * Event for moving the mouse
 *
 * @brief EntryWidget::mouseMoveEvent
 * @param event
 */
void EntryWidget::mouseMoveEvent(QMouseEvent *event)
{
}
