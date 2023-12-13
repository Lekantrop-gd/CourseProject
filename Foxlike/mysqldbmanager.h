#ifndef MYSQLDBMANAGER_H
#define MYSQLDBMANAGER_H

#include <QSqlDatabase>
#include <QVector>
#include "dbmanager.h"

class MySQLDBManager : public DBManager {

public:
    void connectToDataBase() override;

    bool createTables();

protected:
    QSqlDatabase db;
    const QString dataBaseName = "database.db";

    MySQLDBManager();

    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
};

#endif // MYSQLDBMANAGER_H
