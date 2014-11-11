#ifndef FLOWLAYOUT_H
#define FLOWLAYOUT_H

#include <Qt>
#include <QObject>
#include <QLayout>
#include <QWidget>
#include <QLayoutItem>
#include <QSize>
#include <QRect>
#include <QStyle>
#include <QList>

/**
 * @brief The FlowLayout class
 *
 * Layout where elements align in a flow from left to right.
 * This class was created by the given example of a flowlayout.
 * Source: http://qt-project.org/doc/qt-4.8/layouts-flowlayout.html
 * Date: 20.09.2014
 *
 * @author Qt
 */
class FlowLayout : public QLayout
{

public:
    explicit FlowLayout(QWidget *parent, int margin = -1, int hSpacing = -1, int vSpacing = -1);
    explicit FlowLayout(int margin = -1, int hSpacing = -1, int vSpacing = 1);
    ~FlowLayout();

    void addItem(QLayoutItem *item);
    int horizontalSpacing() const;
    int verticalSpacing() const;
    Qt::Orientations expandingDirections() const;
    bool hasHeightForWidth() const;
    int heightForWidth(int) const;
    int count() const;
    QLayoutItem *itemAt(int index) const;
    QSize minimumSize() const;
    void setGeometry(const QRect &rect);
    QSize sizeHint() const;
    QLayoutItem *takeAt(int index);

private:
    int doLayout(const QRect &rect, bool testOnly) const;
    int smartSpacing(QStyle::PixelMetric pm) const;

    QList<QLayoutItem *> itemList;
    int m_hSpace;
    int m_vSpace;

};

#endif // FLOWLAYOUT_H
