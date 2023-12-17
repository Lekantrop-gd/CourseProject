#ifndef USERSDBMANAGER_H
#define USERSDBMANAGER_H
#include "mysqldbmanager.h"
#include "user.h"

class UsersDBManager : public MySQLDBManager
{
public:
    static UsersDBManager* getInstance();

    User* fetchUser(QString nickname, QString password);

private:
    static UsersDBManager* instance;

};

#endif // USERSDBMANAGER_H
