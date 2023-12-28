#include "mysqldbmanager.h"
#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QSqlTableModel>

MySQLDBManager* MySQLDBManager::instance = nullptr;

MySQLDBManager* MySQLDBManager::getInstance() {
    if (instance == nullptr) {
        instance = new MySQLDBManager();
    }
    return instance;
}

MySQLDBManager::MySQLDBManager() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("FoxlikeGames");
    db.setUserName("root");
    db.setPassword("root");

}

bool MySQLDBManager::connectToDataBase() {
    if (db.isOpen())
        return true;

    if (!db.open()) {
        qDebug() << "Error opening database:" << db.lastError().text();
        return false;
    }

    this->createTables();

    return true;
}

bool MySQLDBManager::restoreDataBase() {
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

bool MySQLDBManager::openDataBase() {
    if (db.open()) {
        return true;
    }
    else {
        return false;
    }
}

void MySQLDBManager::closeDataBase() {
    db.close();
}

bool MySQLDBManager::createTables() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS Genres("
                    "genreId INT PRIMARY KEY AUTO_INCREMENT, "
                    "genre VARCHAR(255) NOT NULL UNIQUE)"))
    {
        qDebug() << query.lastError().text();
        return false;
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS Statuses("
                    "statusId INT PRIMARY KEY AUTO_INCREMENT, "
                    "status VARCHAR(255) NOT NULL UNIQUE)"))
    {
        qDebug() << query.lastError().text();
        return false;
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS AccountTypes("
                    "accountTypeId INT PRIMARY KEY AUTO_INCREMENT, "
                    "accountType VARCHAR(255) NOT NULL UNIQUE)"))
    {
        qDebug() << query.lastError().text();
        return false;
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS Games ("
                    "id INT PRIMARY KEY AUTO_INCREMENT, "
                    "title VARCHAR(70) NOT NULL UNIQUE, "
                    "shortDescription VARCHAR(255) NOT NULL UNIQUE, "
                    "fullDescription TEXT NOT NULL UNIQUE, "
                    "price DECIMAL(4, 2) NOT NULL, "
                    "developer VARCHAR(70) NOT NULL, "
                    "publisher VARCHAR(70) NOT NULL, "
                    "releaseDate DATE NOT NULL, "
                    "genre INT NOT NULL, "
                    "banner VARCHAR(80) NOT NULL UNIQUE, "
                    "image VARCHAR(80) NOT NULL UNIQUE, "
                    "icon VARCHAR(80) NOT NULL UNIQUE, "
                    "status INT, "
                    "FOREIGN KEY (genre) REFERENCES Genres(genreId), "
                    "FOREIGN KEY (status) REFERENCES Statuses(statusId))"))
    {
        qDebug() << query.lastError().text();
        return false;
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS Users("
                    "id INTEGER PRIMARY KEY AUTO_INCREMENT, "
                    "nickname varchar(50) UNIQUE, "
                    "password varchar(255) NOT NULL, "
                    "profilePhoto varchar(50) UNIQUE, "
                    "accountType INT NOT NULL, "
                    "status INT NOT NULL, "
                    "FOREIGN KEY (accountType) REFERENCES AccountTypes(accountTypeId), "
                    "FOREIGN KEY (status) REFERENCES Statuses(statusId))"))
    {
        qDebug() << query.lastError().text();
        return false;
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS PurchasedGames("
                    "userId INT, "
                    "gameId INT, "
                    "status INT, "
                    "payment VARCHAR(255), "
                    "FOREIGN KEY (userId) REFERENCES Users(id) ON DELETE CASCADE, "
                    "FOREIGN KEY (gameId) REFERENCES Games(id) ON DELETE CASCADE, "
                    "FOREIGN KEY (status) REFERENCES Statuses(statusId))"))
    {
        qDebug() << query.lastError().text();
        return false;
    }

    return true;
}
