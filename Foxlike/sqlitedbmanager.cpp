#include "sqlitedbmanager.h"
#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QSqlTableModel>

SQLiteDBManager* SQLiteDBManager::instance = nullptr;

SQLiteDBManager* SQLiteDBManager::getInstance() {
    if (instance == nullptr) {
        instance = new SQLiteDBManager();
    }
    return instance;
}

SQLiteDBManager::SQLiteDBManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName(this->dataBaseName);
}

bool SQLiteDBManager::connectToDataBase() {
    if (QFile(this->dataBaseName).exists()) {
        return this->openDataBase();
    }

    else {
        return this->restoreDataBase();
    }
}

bool SQLiteDBManager::restoreDataBase() {
    if (this->openDataBase()) {
        if (!this->createTables()) {
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Unable to restore database";
        return false;
    }
}

bool SQLiteDBManager::openDataBase() {
    if (db.open()) {
        return true;
    } else
        return false;
}

void SQLiteDBManager::closeDataBase() {
    db.close();
}

bool SQLiteDBManager::createTables() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE Games("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "title varchar[70] NOT NULL UNIQUE, "
                    "shortDescription TEXT NOT NULL UNIQUE, "
                    "fullDescription TEXT NOT NULL UNIQUE, "
                    "price DECIMAL(4, 2) NOT NULL, "
                    "developer varchar[70] NOT NULL, "
                    "publisher varchar[70] NOT NULL, "
                    "releaseDate DATE NOT NULL, "
                    "genre varchar[30] NOT NULL, "
                    "banner varchar[80] NOT NULL UNIQUE, "
                    "image varchar[80] NOT NULL UNIQUE, "
                    "icon varchar[80] NOT NULL UNIQUE, "
                    "status varchar[11] CHECK(status IN('confirmed', 'unconfirmed')) NOT NULL DEFAULT 'unconfirmed'"
                    ");"))
    {
        qDebug() << query.lastError().text();
        return false;
    }

    if (!query.exec("CREATE TABLE Users("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "nickname varchar[50] UNIQUE, "
                    "password TEXT NOT NULL, "
                    "profilePhoto varchar[50] UNIQUE, "
                    "accountType varchar[10] CHECK(accountType IN ('guest', 'user', 'developer', 'admin')) NOT NULL DEFAULT 'guest', "
                    "status varchar[11] CHECK(status IN('confirmed', 'unconfirmed')) NOT NULL DEFAULT 'unconfirmed'"
                    ")"))
    {
        qDebug() << query.lastError().text();
        return false;
    }

    if (!query.exec("CREATE TABLE PurchasedGames("
                    "userId INT REFERENCES Users(id), "
                    "gameId INT REFERENCES Games(id), "
                    "status varchar[11] CHECK(status IN('confirmed', 'unconfirmed')) NOT NULL DEFAULT 'unconfirmed'"
                    "payment TEXT"
                    ")"))
    {
        qDebug() << query.lastError().text();
        return false;
    }

    return true;
}
