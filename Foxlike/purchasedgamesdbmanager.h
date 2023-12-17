#ifndef PURCHASEDGAMESDBMANAGER_H
#define PURCHASEDGAMESDBMANAGER_H
#include "mysqldbmanager.h"
#include "game.h"

class PurchasedGamesDBManager// : public MySQLDBManager
{
public:
    static PurchasedGamesDBManager* getInstance();

    QVector<Game> getGamesOfUserById(int id);

private:
    PurchasedGamesDBManager() = default;

    static PurchasedGamesDBManager* instance;

    //virtual void connectToDataBase();

    //virtual bool createTables();
};

#endif // PURCHASEDGAMESDBMANAGER_H
