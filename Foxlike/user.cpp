#include "user.h"
#include <QDebug>

User::User(QVector<Game> games, EntryWindow *entryWindow) : games(games)
{
    connect(entryWindow, &EntryWindow::userLoggedIn, this, &User::onUserLoggedIn);
}

AccountType User::getAccountType() const
{
    return accountType;
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

void User::onUserLoggedIn(QString profilePhoto, QString nickname, AccountType accountType)
{
    this->profilePhoto = profilePhoto;
    this->nickname = nickname;
    this->accountType = accountType;
}
