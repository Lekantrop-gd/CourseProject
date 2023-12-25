#include "purchasedgamesdbmanager.h"
#include "gamesdbmanager.h"
#include "qsqlerror.h"
#include "QFile"
#include <QSqlQuery>

PurchasedGamesDBManager* PurchasedGamesDBManager::instance = nullptr;

PurchasedGamesDBManager* PurchasedGamesDBManager::getInstance() {
    if (instance == nullptr) {
        instance = new PurchasedGamesDBManager();
    }
    return instance;
}

QVector<Game> PurchasedGamesDBManager::getGamesOfUserById(int id)
{
    QSqlQuery query;
    GamesDBManager *gamesDBManager = GamesDBManager::getInstance();
    QVector<Game> games;

    query.prepare("SELECT gameId FROM PurchasedGames WHERE userId = :id AND status = 'confirmed'");
    query.bindValue(":id", id);

    if (query.exec()) {
        while (query.next()) {
            games.push_back(gamesDBManager->getGameById(query.value(0).toInt()));
        }
    }

    return games;
}

bool PurchasedGamesDBManager::addPurchase(int userId, int gameId, QString payment)
{
    QSqlQuery query;

    if (query.prepare("")) {

    }

    query.prepare("INSERT INTO PurchasedGames(userId, gameId, status, payment) VALUES(:userId, :gameId, 'unconfirmed', :payment)");
    query.bindValue(":userId", userId);
    query.bindValue(":gameId", gameId);
    query.bindValue(":payment", payment);

    if (query.exec()) {
        return true;
    }

    qDebug() << query.lastError();
    return false;
}

void PurchasedGamesDBManager::deletePurchaseByGameId(int gameId)
{
    QSqlQuery query;

    query.prepare("SELECT userId, gameId FROM PurchasedGames WHERE gameId = :gameId");
    query.bindValue(":gameId", gameId);
    if (query.exec()) {
        if (query.next()) {
            QString payment = query.value(0).toString() + query.value(1).toString();

            query.prepare("DELETE FROM PurchasedGames WHERE gameId = :gameId");
            query.bindValue(":gameId", gameId);

            if (query.exec()) {
                QFile::remove(payment);
            }
        }
    }





}
