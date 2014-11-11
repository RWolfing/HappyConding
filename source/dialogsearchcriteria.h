#ifndef DIALOGSEARCHCRITERIA_H
#define DIALOGSEARCHCRITERIA_H

#include <QDialog>
#include <QString>
#include <QMap>


namespace Ui {
class DialogSearchCriteria;
}

/**
 * @brief The DialogSearchCriteria class
 *
 * This class represents the QDialog to set the search criteria.
 *
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */
class DialogSearchCriteria : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSearchCriteria(QWidget *parent = 0);
    ~DialogSearchCriteria();

    static const QString KEY_PATTERN()
      { return "keypattern"; }
    static const QString KEY_LANGUAGE()
      { return "keylanguage"; }
    static const QString KEY_NAME_AUTHOR()
      { return "keyauthor"; }
    static const QString KEY_NAME_ENTRY()
      { return "keyentry"; }
    static const QString KEY_CODE()
      { return "keycode"; }
    static const QString KEY_DESCR()
      { return "keydescr"; }
    static const QString KEY_DATE()
      { return "keydate"; }

    QMultiMap<QString, QString> getCriteriaMap();


private slots:

    void on_bttnGo_clicked();

private:
    Ui::DialogSearchCriteria *ui;
    QMultiMap<QString, QString> criteriaMap;

    void createPatternLayout();
    void createLanguageLayout();
};

#endif // DIALOGSEARCHCRITERIA_H
