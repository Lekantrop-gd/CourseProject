#include "usersdbmanager.h"
#include "purchasedgamesdbmanager.h"
#include "qsqlerror.h"
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

    query.prepare("SELECT Users.id, Users.nickname, Users.password, Users.profilePhoto, AccountTypes.accountType "
                  "FROM Users JOIN AccountTypes ON (Users.accountType = AccountTypes.accountTypeId) WHERE nickname = :nickname");

    query.bindValue(":nickname", nickname);

    if (query.exec()) {
        if (query.next()) {
            if (query.value(2).toString() == QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex())) {
                PurchasedGamesDBManager *purchasedGamesDBManager = PurchasedGamesDBManager::getInstance();
                AccountType accountType;

                if (query.value(4).toString() == "user") accountType = AccountType::user;
                else if (query.value(4).toString() == "developer") accountType = AccountType::developer;
                else if (query.value(4).toString() == "contentManager") accountType = AccountType::contentManager;
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

bool UsersDBManager::checkIfUserExists(QString nickname)
{
    QSqlQuery query;

    query.prepare("SELECT nickname FROM Users WHERE nickname = :nickname AND "
                  "status = (SELECT statusId FROM Statuses WHERE status = 'confirmed')");

    query.bindValue(":nickname", nickname);

    if (query.exec()) {
        query.next();
        return query.isValid();
    }

    return false;
}

bool UsersDBManager::insertUserIntoTable(const User &user, QString password)
{
    QSqlQuery query;

    query.prepare("INSERT INTO Users(nickname, password, profilePhoto, accountType, status)"
                  "VALUES(:nickname, :password, :profilePhoto, :accountType, (SELECT statusId FROM Statuses WHERE status = 'unconfirmed'))");

    query.bindValue(":nickname", user.getNickname());
    query.bindValue(":password", QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex()));
    query.bindValue(":profilePhoto", user.getProfilePhoto());

    switch (user.getAccountType()) {
        case AccountType::developer:
            query.bindValue(":accountType", "2");
            break;

        case AccountType::contentManager:
            query.bindValue(":accountType", "3");
            break;

        default:
            query.bindValue(":accountType", "1");
            break;
    };

    if (query.exec()) {
        return true;
    }

    qDebug() << query.lastError();

    return false;
}

QVector<QString> UsersDBManager::getAccountTypes()
{
    QSqlQuery query;
    QVector<QString> accountTypes;

    if (query.exec("SELECT accountType FROM AccountTypes")) {
        while (query.next()) {
            accountTypes.push_back(query.value(0).toString());
        }
    }

    return accountTypes;
}
