#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{
    this->closeDataBase();
}

void DataBase::connectToDataBase()
{
    if(!QFile(DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Could not restore database";
        return false;
    }
    return false;
}

bool DataBase::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

void DataBase::closeDataBase()
{
    db.close();
}

bool DataBase::createTable()
{
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE IF NOT EXISTS " TABLE " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            PLAN       " DATEAND            NOT NULL,"
                            DEADLINE   " DATETIME           NOT NULL,"
                            STATUS     " BOOL               DEFAULT 0,"
                            IMPORTANCE " INTEGER            NOT NULL,"
                            URGENCY    " INTEGER            NOT NULL"
                        " )"
                    )){
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}


