#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>

class DBManager {
public:
    virtual void connectToDataBase() = 0;
};

#endif // DBMANAGER_H
