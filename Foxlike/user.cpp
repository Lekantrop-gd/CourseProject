#include "user.h"

AccountType User::getAccountType() const
{
    return accountType;
}

int User::getId() const
{
    return id;
}

QString User::getProfilePhoto() const
{
    return profilePhoto;
}

QString User::getNickname() const
{
    return nickname;
}

QVector<Game> User::getGames() const
{
    return games;
}

User::User(int id, const QString &nickname, const QString &profilePhoto, const QVector<Game> &games, AccountType accountType) :
    id(id),
    nickname(nickname),
    profilePhoto(profilePhoto),
    games(games),
    accountType(accountType)
{}

User::User(User *user)
{
    this->id = user->id;
    this->nickname = user->nickname;
    this->profilePhoto = user->profilePhoto;
    this->games = user->games;
    this->accountType = user->accountType;
}

User::User()
{
    this->id = 0;
    this->nickname = NULL;
    this->profilePhoto = NULL;
    this->accountType = AccountType::guest;
}
