#include "headerwidget.h"
#include "ui_headerwidget.h"


/**
 * Constructs the widget from the given parent.
 *
 * @brief HeaderWidget::HeaderWidget
 * @param parent
 */
HeaderWidget::HeaderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeaderWidget)
{
    ui->setupUi(this);
}

/**
 * Deconstructs the widget.
 *
 * @brief HeaderWidget::~HeaderWidget
 */
HeaderWidget::~HeaderWidget()
{
    delete ui;
}
