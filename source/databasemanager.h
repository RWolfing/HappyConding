#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

/**
 * @brief The DatabaseManager class
 *
 * databasemanager.h
 * This manages the connection of the programm to the database.
 *
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */


class DatabaseManager : public QObject
    {
    public:
        DatabaseManager(QObject *parent = 0);
        ~DatabaseManager();

        bool setupDB();
        bool setupDBTables();

        QSqlError lastError();

        QSqlQuery getEntries(QString sqlStatement);
        QSqlDatabase getDatabase();
        QString getSQLError();

    private:
        QSqlDatabase database;
        QString databasePath;
        QString error;

        void setError(QString alert);
    };

#endif // DATABASEMANAGER_H
