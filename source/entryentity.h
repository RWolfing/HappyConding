#ifndef ENTRYENTITY_H
#define ENTRYENTITY_H

#include <QString>
#include <QColor>


/**
 * @brief The EntryEntity class
 *
 *  This class is used to represent the entry table in the database.
 *
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */
class EntryEntity
{
public:
    EntryEntity(int ID, QString entryName, QString entryDate,
                QString authorName, QString entryCode,
                QString pattern, QString system,
                QString lang, QString descr, int sourcesKey);
    EntryEntity();
    ~EntryEntity();

    void setEntryId(int id);

    void setEntryName(QString entryName);

    void setEntryDate(QString entryDate);

    void setAuthorName(QString authorName);

    void setEntryCode(QString entryCode);

    void setPattern(QString pattern);

    void setLanguage(QString language);

    void setSystem(QString system);

    void setDescription(QString description);

    void setSourceKey(int key);

    int getEntryId();

    QString getEntryName();

    QString getEntryDate();

    QString getAuthorName();

    QString getEntryCode();

    QString getPattern();

    QString getSystem();

    QString getLanguage();

    QString getDescription();

    int getSourceKey();

private:

    int ID;
    QString name;
    QString date;
    QString authorName;
    QString code;
    QString pattern;
    QString system;
    QString lang;
    QString descr;
    int sources;

};

#endif // ENTRYENTITY_H
