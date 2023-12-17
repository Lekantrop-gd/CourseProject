#include "usersdbmanager.h"
#include "purchasedgamesdbmanager.h"
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
    QSqlQuery query;

    query.prepare("SELECT id, nickname, password, profilePhoto, accountType FROM Users WHERE nickname = :nickname");
    query.bindValue(":nickname", nickname);

    if (query.exec()) {
        if (query.next()) {
            if (query.value(2).toString() == QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex())) {
                PurchasedGamesDBManager *purchasedGamesDBManager = PurchasedGamesDBManager::getInstance();
                AccountType accountType;

                if (query.value(4).toString() == "user") accountType = AccountType::guest;
                else if (query.value(4).toString() == "developer") accountType = AccountType::developer;
                else if (query.value(4).toString() == "admin") accountType = AccountType::admin;
                else accountType = AccountType::guest;

                User *user = new User(
                    query.value(0).toInt(),
                    query.value(1).toString(),
                    query.value(3).toString(),
                    purchasedGamesDBManager->getGamesOfUserById(query.value(0).toInt()),
                    accountType);

                return user;
            }
        }
    }

    return nullptr;
}

