#ifndef USER_H
#define USER_H
#include <QString>
#include "game.h"
#include "Enums.h"

class User
{
public:
    User(int id, const QString &nickname, const QString &profilePhoto, const QVector<Game> &games, AccountType accountType);

    User(User* user);

    User();

    int getId() const;

    QString getNickname() const;

    QString getProfilePhoto() const;

    QVector<Game> getGames() const;

    AccountType getAccountType() const;

private:
    int id;
    QString nickname;
    QString profilePhoto;
    QVector<Game> games;
    AccountType accountType = AccountType::guest;
};

#endif // USER_H
