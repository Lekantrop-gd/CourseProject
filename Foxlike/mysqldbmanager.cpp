#include "mysqldbmanager.h"
#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QSqlTableModel>

MySQLDBManager::MySQLDBManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName(this->dataBaseName);
}

void MySQLDBManager::connectToDataBase() {
    if (QFile(this->dataBaseName).exists()) {
        this->openDataBase();
    } else {
        this->restoreDataBase();
    }
}

bool MySQLDBManager::restoreDataBase() {
    if (this->openDataBase()) {
        if (!this->createTables()) {
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не вдалось відновити базу даних";
        return false;
    }
}

bool MySQLDBManager::openDataBase() {
    if (db.open()) {
        return true;
    } else
        return false;
}

void MySQLDBManager::closeDataBase() {
    db.close();
}

bool MySQLDBManager::createTables() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE Games("
                    "id INT PRIMARY KEY, "
                    "title varchar[70] NOT NULL, "
                    "shortDescription TEXT NOT NULL, "
                    "fullDescription TEXT NOT NULL, "
                    "price DECIMAL(4, 2) NOT NULL, "
                    "developer varchar[70] NOT NULL, "
                    "publisher varchar[70] NOT NULL, "
                    "releaseDate DATE NOT NULL, "
                    "genre varchar[30] NOT NULL, "
                    "banner varchar[80] NOT NULL, "
                    "image varchar[80] NOT NULL, "
                    "icon varchar[80] NOT NULL"
                    ");"))
    {
        qDebug() << query.lastError().text();
        return false;
    }

    return true;
}
