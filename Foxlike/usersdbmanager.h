#ifndef USERSDBMANAGER_H
#define USERSDBMANAGER_H
#include "user.h"

class UsersDBManager
{
public:
    static UsersDBManager* getInstance();

    User* fetchUser(QString nickname, QString password);
    bool checkIfUserExists(QString nickname);
    bool insertUserIntoTable(const User& user, QString password);
    QVector<QString> getAccountTypes();

private:
    UsersDBManager() = default;

    static UsersDBManager* instance;
};

#endif // USERSDBMANAGER_H
