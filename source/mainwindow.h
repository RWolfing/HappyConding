#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialognewentry.h"
#include "dialogsearchcriteria.h"
#include "flowlayout.h"
#include <QColor>

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 *
 * This class represents the mainwindow of the application.
 *
 * @author Robert Wolfinger
 * @version 1.0 20.09.2014
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

   static QColor calculateTextColor(QColor background);


private slots:
    void open_NewEntryDialog();
    void open_SettingsDialog();
    void open_HelpDialog();

    void closed_CriteriaDialog();

    void on_bttnSearch_clicked();
    void on_bttnCustomize_clicked();

    void on_bttnHelp_clicked();

private:
    Ui::MainWindow *ui;
    FlowLayout *flowLayoutCriteria;
    FlowLayout *flowLayoutEntries;

    DialogSearchCriteria *dialogSearchCriteria;

    QMultiMap<QString, QString> *criteria;

    void doSearch();
    void clearCriteriaFlowLayout();
    void clearEntriesFlowLayout();

};

#endif // MAINWINDOW_H
