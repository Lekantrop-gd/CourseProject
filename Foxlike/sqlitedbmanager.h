#ifndef SQLITEDBMANAGER_H
#define SQLITEDBMANAGER_H

#include <QSqlDatabase>
#include <QVector>
#include "dbmanager.h"

class SQLiteDBManager : public DBManager {

public:
    static SQLiteDBManager* getInstance();

    virtual bool connectToDataBase();

    virtual bool createTables();

private:
    SQLiteDBManager();

    QSqlDatabase db;

    static SQLiteDBManager* instance;

    const QString dataBaseName = "database.db";

    bool openDataBase() override;
    bool restoreDataBase() override;
    void closeDataBase() override;
};

#endif // SQLITEDBMANAGER_H
