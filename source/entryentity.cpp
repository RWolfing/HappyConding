/**
 * @author Robert Wolfinger
 * @version 1.0 20.09.14
 */

#include "entryentity.h"

/**
 * Constructor for an empty entry.
 *
 * @brief EntryEntity::EntryEntity
 */
EntryEntity::EntryEntity()
{
    setEntryName("");
    setEntryDate("");
    setAuthorName("");
    setEntryCode("");
    setPattern("");
    setSystem("");
    setLanguage("");
    setDescription("");
    setSourceKey(0);
}

/**
 * Constructor for an entry.
 *
 * @brief EntryEntity::EntryEntity
 * @param ID
 * @param entryName
 * @param entryDate
 * @param authorName
 * @param entryCode
 * @param pattern
 * @param system
 * @param lang
 * @param descr
 * @param sourcesKey
 */
EntryEntity::EntryEntity(int ID, QString entryName, QString entryDate, QString authorName,
                         QString entryCode, QString pattern, QString system,
                         QString lang, QString descr, int sourcesKey)
{

    setEntryId(ID);
    setEntryName(entryName);
    setEntryDate(entryDate);
    setAuthorName(authorName);
    setEntryCode(entryCode);
    setPattern(pattern);
    setSystem(system);
    setLanguage(lang);
    setDescription(descr);
    setSourceKey(sourcesKey);

}

/**
 * Deconstructor for the entity object.
 *
 * @brief EntryEntity::~EntryEntity
 */
EntryEntity::~EntryEntity()
{
}

void EntryEntity::setEntryId(int id)
{
    this->ID = id;
}

void EntryEntity::setEntryName(QString entryName){
    this->name = entryName;
}

void EntryEntity::setEntryDate(QString entryDate)
{
    this->date = entryDate;
}

void EntryEntity::setAuthorName(QString authorName)
{
    this->authorName = authorName;
}

void EntryEntity::setEntryCode(QString entryCode)
{
    this->code = entryCode;
}

void EntryEntity::setPattern(QString pattern)
{
    this->pattern = pattern;
}

void EntryEntity::setLanguage(QString language)
{
    this->lang = language;
}

void EntryEntity::setSystem(QString system)
{
    this->system = system;
}

void EntryEntity::setDescription(QString description)
{
    this->descr = description;
}

void EntryEntity::setSourceKey(int key)
{
    this->sources = key;
}

int EntryEntity::getEntryId()
{
    return this->ID;
}

QString EntryEntity::getEntryName()
{
    return this->name;
}

QString EntryEntity::getEntryDate()
{
    return this->date;
}

QString EntryEntity::getAuthorName()
{
    return this->authorName;
}

QString EntryEntity::getEntryCode()
{
    return this->code;
}

QString EntryEntity::getPattern()
{
    return this->pattern;
}

QString EntryEntity::getSystem()
{
    return this->system;
}

QString EntryEntity::getLanguage()
{
    return this->lang;
}

QString EntryEntity::getDescription()
{
    return this->descr;
}

int EntryEntity::getSourceKey()
{
    return this->sources;
}
