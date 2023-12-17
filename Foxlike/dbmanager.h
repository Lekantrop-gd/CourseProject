#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>

class DBManager {
public:
    virtual bool openDataBase() = 0;
    virtual bool restoreDataBase() = 0;
    virtual void closeDataBase() = 0;
};

#endif // DBMANAGER_H
