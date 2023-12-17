#include "usersdbmanager.h"
#include "gamesdbmanager.h"
#include <QSqlQuery>
#include <QCryptographicHash>


UsersDBManager* UsersDBManager::instance = nullptr;

UsersDBManager* UsersDBManager::getInstance() {
    if (instance == nullptr) {
        instance = new UsersDBManager();
    }
    return instance;
}

User* UsersDBManager::fetchUser(QString nickname, QString password)
{
    qDebug() << QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());

    QSqlQuery query;

    query.prepare("SELECT * FROM Users WHERE nickname = :nickname");
    query.bindValue(":nickname", nickname);

    if (query.exec()) {
        if (query.next()) {
            if (query.value(2).toString() == QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex())) {
                GamesDBManager *gamesDBManager = GamesDBManager::getInstance();
                AccountType accountType;

                if (query.value(4).toString() == "user") accountType = AccountType::guest;
                else if (query.value(4).toString() == "developer") accountType = AccountType::developer;
                else if (query.value(4).toString() == "admin") accountType = AccountType::admin;
                else accountType = AccountType::guest;

                User *user = new User(
                    query.value(0).toInt(),
                    query.value(1).toString(),
                    query.value(2).toString(),
                    gamesDBManager->getAllGames(),
                    accountType);

                return user;
            }
            else {
                //Wrong password
            }
        }
    }

    //There is no user with that nickname
    return nullptr;
}

