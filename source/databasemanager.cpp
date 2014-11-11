/**
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */

#include "databasemanager.h"
#include <QDir>
#include <QSqlQuery>
#include <QMessageBox>

#define DATABASE_FILE_NAME "codeDB.db"
#define TABLE_NAME_ENTRIES "Entries"
#define SQL_TAG_ENTRYNAME "EntryName"
#define SQL_TAG_ENTRYDATE "EntryDate"
#define SQL_TAG_AUTORNAME "AutorName"
#define SQL_TAG_CODE "EntryCode"
#define SQL_TAG_PATTERN "Pattern"
#define SQL_TAG_SYSTEM "System"
#define SQL_TAG_SOURCES "Sources"
#define SQL_TAG_DESCRIPTION "CodeDescription"
#define SQL_TAG_LANGUAGE "CodeLanguage"


/**
 * Constructs the DatabaseManager with the given parent.
 *
 * @brief DatabaseManager::DatabaseManager
 * @param parent
 */
DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{   
}

/**
 * Deconstructs the DatabaseManager.
 * All changes are being comitted and the connection is closed.
 *
 * @brief DatabaseManager::~DatabaseManager
 */

DatabaseManager::~DatabaseManager()
{
    database.commit();
    database.close();
}

/**
 * Sets up the databaseconnection of the DatabaseManager.
 *
 * @brief DatabaseManager::setupDB
 * @return success of the setup
 */
bool DatabaseManager::setupDB()
{
    database = QSqlDatabase::addDatabase( "QSQLITE" );
    databasePath = ".";
    databasePath.append(QDir::separator()).append(DATABASE_FILE_NAME);
    database.setDatabaseName(databasePath);

    if(!database.open() )
    {
      QMessageBox::critical(0, QObject::tr("Database Error"), database.lastError().text());
      return false;
    }

    return setupDBTables();

}

/**
 * Creates all necessary tables in the database if they do not already exist.
 *
 *
 * @brief DatabaseManager::setupDBTables
 * @return success of setting up tables
 */
bool DatabaseManager::setupDBTables()
{
    QSqlQuery query;

    //CREATE TABLE ENTRIES
    QString queryStatment = "CREATE TABLE IF NOT EXISTS " TABLE_NAME_ENTRIES
            "(ID INTEGER UNIQUE PRIMARY KEY, "
            SQL_TAG_ENTRYNAME " TEXT, "
            SQL_TAG_ENTRYDATE " TEXT, "
            SQL_TAG_AUTORNAME " TEXT, "
            SQL_TAG_CODE " TEXT, "
            SQL_TAG_PATTERN " TEXT, "
            SQL_TAG_SYSTEM " TEXT, "
            SQL_TAG_LANGUAGE " TEXT, "
            SQL_TAG_DESCRIPTION " TEXT, "
            SQL_TAG_SOURCES " INTEGER)";

    query.prepare(queryStatment);
    if(!query.exec())
    {
     setError("Creating Table Entries failed... " + query.lastError().text());
     return false;
    }

    //CREATE TABLE LANGUAGES
    queryStatment = "CREATE TABLE IF NOT EXISTS Languages "
            "(ID INTEGER PRIMARY KEY AUTOINCREMENT, "
            "Language TEXT NOT NULL UNIQUE COLLATE NOCASE, "
            "Color TEXT NOT NULL DEFAULT '#00ffffff');";

    query.prepare(queryStatment);
    if(!query.exec())
    {
     setError("Creating Table Languages failed... " + query.lastError().text());
     return false;
    }

    //CREATE TABLE PATTERNS
    queryStatment = "CREATE TABLE IF NOT EXISTS Patterns "
            "(ID INTEGER PRIMARY KEY AUTOINCREMENT, "
            "Pattern TEXT NOT NULL UNIQUE COLLATE NOCASE DEFAULT '', "
            "Color TEXT NOT NULL DEFAULT '#00ffffff');";

    query.prepare(queryStatment);
    if(!query.exec())
    {
     setError("Creating Table Patterns failed... " + query.lastError().text());
     return false;
    }



    return true;
}

/**
 *  Returns the last error of the database.
 *
 *  @brief DatabaseManager::lastError
 * @return Last error of the database
 */
QSqlError DatabaseManager::lastError()
    {
    return database.lastError();
    }

/**
 * Returns the database of the DatabaseManager.
 *
 * @brief DatabaseManager::getDatabase
 * @return database
 */
QSqlDatabase DatabaseManager::getDatabase()
{
    return database;
}

/**
 * Sets the error of the DatabaseManager from the given alert. This can be used to set
 * for example a SQLError which is not a DatabaseError.
 *
 * @brief DatabaseManager::setError
 * @param alert
 */
void DatabaseManager::setError(QString alert)
{
    error = alert;
     QMessageBox::critical(0, QObject::tr("Database Error"),
                           error);
}

/**
 * Returns the set SQLError of the DatabaseManager.
 *
 * @brief DatabaseManager::getSQLError
 * @return SQLError
 */
QString DatabaseManager::getSQLError()
{
    return error;
}

