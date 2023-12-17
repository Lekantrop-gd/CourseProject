#ifndef MYSQLDBMANAGER_H
#define MYSQLDBMANAGER_H

#include <QSqlDatabase>
#include <QVector>
#include "dbmanager.h"

class MySQLDBManager : public DBManager {

public:
    static MySQLDBManager* getInstance();

    virtual void connectToDataBase();

    virtual bool createTables();

protected:
    MySQLDBManager();

    QSqlDatabase db;

    static MySQLDBManager* instance;

private:
    const QString dataBaseName = "database.db";

    bool openDataBase() override;
    bool restoreDataBase() override;
    void closeDataBase() override;
};

#endif // MYSQLDBMANAGER_H
