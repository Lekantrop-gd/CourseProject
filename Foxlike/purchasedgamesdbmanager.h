#ifndef PURCHASEDGAMESDBMANAGER_H
#define PURCHASEDGAMESDBMANAGER_H
#include "game.h"

class PurchasedGamesDBManager
{
public:
    static PurchasedGamesDBManager* getInstance();

    QVector<Game> getGamesOfUserById(int id);

    bool addPurchase(int userId, int gameId, QString payment);

    void deletePurchaseByGameId(int gameId);

private:
    PurchasedGamesDBManager() = default;

    static PurchasedGamesDBManager* instance;
};

#endif // PURCHASEDGAMESDBMANAGER_H
