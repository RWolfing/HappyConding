/**
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */

#include "simplecriteria.h"
#include "ui_simplecriteria.h"
#include <QString>
#include <QMultiMap>
#include <QSqlQuery>
#include "dialogsearchcriteria.h"
#include <QSqlError>
#include <QSqlRecord>
#include <QColor>
#include "qdebug.h"

#include <QMessageBox>
#include <QPainter>
#include <QPainterPath>
#include <QPen>

#include "mainwindow.h"


/**
 * Constructs the widget with the given paramters. Retrieves the title and color from the given mapKey and criteriaMap.
 *
 * @brief SimpleCriteria::SimpleCriteria
 * @param parent
 * @param mapKey
 * @param criteriaMap
 */
SimpleCriteria::SimpleCriteria(QWidget *parent, QString mapKey, QMultiMap<QString, QString> *criteriaMap) :
    QWidget(parent),
    ui(new Ui::SimpleCriteria)
{
    ui->setupUi(this);

    if(!criteriaMap)
    {
        criteriaMap = new QMultiMap<QString, QString>();
    }

    criteria = criteriaMap;
    key = mapKey;
    content = criteria->value(key, "default");

    this->color = QColor(255, 255, 255);

    if((key != DialogSearchCriteria::KEY_PATTERN()) && (key != DialogSearchCriteria::KEY_LANGUAGE()))
        setupColor();

    if(key == DialogSearchCriteria::KEY_CODE())
    {
        ui->lblContent->setText("Codefilter");
        return;
    }
    if(key == DialogSearchCriteria::KEY_DESCR())
    {
        ui->lblContent->setText("Beschreibungsfilter");
        return;
    }

    ui->lblContent->setText(content);
}

/**
 * Deconstructs the widget.
 *
 * @brief SimpleCriteria::~SimpleCriteria
 */
SimpleCriteria::~SimpleCriteria()
{
    delete ui;
}

/**
 * Removes the widgets' key and title from the criterias.
 * Deletes the widget.
 *
 * @brief SimpleCriteria::on_bttnRemove_clicked
 */
void SimpleCriteria::on_bttnRemove_clicked()
{
    if(criteria)
    criteria->remove(key, content);
    delete this;
}

/**
 * Sets the title of the widget to the given text.
 *
 * @brief SimpleCriteria::setContent
 * @param text
 */
void SimpleCriteria::setContent(QString text)
{
    ui->lblContent->setText(text);
    content = text;
    setupColor();
}

/**
 * Sets up the background color of the widget.
 * Depending on the mapKey the color is being retrieved from the database
 * and set as the background color.
 *
 * @brief SimpleCriteria::setupColor
 */
void SimpleCriteria::setupColor()
{
    QString color;
    QString queryStatement;
    QString name = this->content;
    QString mapKey = key;

    if(mapKey == DialogSearchCriteria::KEY_PATTERN())
    {
        queryStatement = QString("Select Color FROM Patterns WHERE Pattern LIKE '%1';").arg(name);
    }

    if(mapKey == DialogSearchCriteria::KEY_LANGUAGE())
    {
         queryStatement = QString("Select Color FROM Languages WHERE Language LIKE '%1';").arg(name);
    }

    if(mapKey == DialogSearchCriteria::KEY_CODE())
    {
        color = "#4dba22";
    }

    if(mapKey == DialogSearchCriteria::KEY_DESCR())
    {
        color = "#dbb67a";
    }

    if(mapKey == DialogSearchCriteria::KEY_NAME_AUTHOR())
    {
        color = "#d9d9d9";
    }

    if(mapKey == DialogSearchCriteria::KEY_NAME_ENTRY())
    {
        color = "#ffcb00";
    }

    if(!queryStatement.isEmpty())
    {
        QSqlQuery query;
        query.prepare(queryStatement);

        if(!query.exec())
        {
            QMessageBox::critical(0, "DatabaseError", "Couldnt retrieve color..." + query.lastError().text());
            qDebug() << "SimpleCriteria failed to exec... " << query.lastError();
            return;
        }

        if(query.first())
        {
        color = query.value(0).toString();
        }
        else
        {
            qDebug() << "Query fehler farbe";
        }
    }

    this->color = QColor(color);

    //Set textcolor
    QString textStyle = "color: ";
    QColor textColor = MainWindow::calculateTextColor(QColor(color));
    textStyle.append(textColor.name()).append(";");
    ui->lblContent->setStyleSheet(textStyle);


    QPalette Pal(palette());
    // set black background
    Pal.setColor(QPalette::Background, this->color);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);



}

/**
 * Paintevent of the widget.
 * This was overwritten in order to style the widget.
 *
 * @brief SimpleCriteria::paintEvent
 * @param event
 */
void SimpleCriteria::paintEvent(QPaintEvent *event)
{

    QWidget::paintEvent(event);
    QPainter *painter = new QPainter(this);
    painter->setRenderHint( QPainter::Antialiasing );

    QPen pen(Qt::gray);
    pen.setWidth(2);

    painter->setPen(pen);

    //Border-Top
    painter->drawLine(0, 0, this->width(), 0);

    //Border-Right
    painter->drawLine(this->width(), 0, this->width(), this->height());

    //Border-Bottom
    painter->drawLine(0, this->height(), this->width(), this->height());

    //Border-Left
    painter->drawLine(0, 0, 0, this->height());

    //Rectangle around Button
    int pos1 = this->width() - ui->bttnRemove->width();
    QPainterPath path;
    path.moveTo(pos1, 0);
    path.lineTo(pos1, this->height() / 2);
    path.lineTo(this->width(), this->height() * 0.75);
    path.lineTo(this->width(), 0);
    path.lineTo(pos1, 0);

    //painter.setPen (Qt::NoPen);
    painter->fillPath(path, QBrush(QColor("gray")));
    painter->end();

    delete painter;
}
