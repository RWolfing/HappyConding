/**
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */

#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <QFile>
#include "qdebug.h"
#include "databasemanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //Setup Style
    QString path = ":/styles.qss";
    path = QDir::toNativeSeparators(path);

    QFile styleFile(path);
    styleFile.open(QFile::ReadOnly);

    QString style(styleFile.readAll());
    a.setStyleSheet(style);

    //Setup database
    DatabaseManager dbManager;
    if(!dbManager.setupDB())
        return 1;


    MainWindow w;
    w.show();

    return a.exec();
}
