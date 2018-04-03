#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDebug>
#include <QFile>

#define DATABASE_NAME           "myplans.db"

#define TABLE                   "PLANS"
#define PLAN                    "PLAN"
#define DEADLINE                "DEADLINE"
#define IMPORTANCE              "IMPORTANCE"
#define URGENCY                 "URGENCY"
#define STATUS                  "STATUS"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    void connectToDataBase();

private:
    QSqlDatabase    db;

private:
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable();
};

#endif // DATABASE_H
