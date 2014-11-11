#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QWidget>

namespace Ui {
class HeaderWidget;
}

/**
 * @brief The HeaderWidget class
 *
 * This class represents a widget to visualize the header of the application.
 * So far there is no logic in this widget it is simply used to be able to put two layers of background on each other.
 */
class HeaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderWidget(QWidget *parent = 0);
    ~HeaderWidget();

private:
    Ui::HeaderWidget *ui;
};

#endif // HEADERWIDGET_H
