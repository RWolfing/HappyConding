#ifndef SIMPLECRITERIA_H
#define SIMPLECRITERIA_H

#include <QWidget>
#include <QString>

namespace Ui {
class SimpleCriteria;
}


/**
 * @brief The SimpleCriteria class
 *
 * This class represents a widget to visualize a criteria in the MainWindow.
 *
 * @author Robert Wolfinger
 * @version 1.0 20.09.2014
 */
class SimpleCriteria : public QWidget
{
    Q_OBJECT

public:
    explicit SimpleCriteria(QWidget *parent = 0, QString mapKey = "default", QMultiMap<QString, QString> *criteriaMap = NULL);
    ~SimpleCriteria();

    void setContent(QString text);

private slots:
    void on_bttnRemove_clicked();

protected:

    void paintEvent(QPaintEvent *event);

private:
    Ui::SimpleCriteria *ui;
    QMultiMap<QString, QString> *criteria;

    QString key;
    QString content;
    QColor color;

    void setupColor();

};

#endif // SIMPLECRITERIA_H
