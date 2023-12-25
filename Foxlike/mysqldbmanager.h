#ifndef MYSQLDBMANAGER_H
#define MYSQLDBMANAGER_H

#include <QSqlDatabase>
#include <QVector>
#include "dbmanager.h"

class MySQLDBManager : public DBManager {

public:
    static MySQLDBManager* getInstance();

    virtual bool connectToDataBase();

    virtual bool createTables();

private:
    MySQLDBManager();

    QSqlDatabase db;

    static MySQLDBManager* instance;

    const QString dataBaseName = "database.db";

    bool openDataBase() override;
    bool restoreDataBase() override;
    void closeDataBase() override;
};

#endif // MYSQLDBMANAGER_H
