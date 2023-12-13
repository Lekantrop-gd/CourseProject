#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>
#include "entrywindow.h" //Порушення ISP
#include "game.h"

class User : public QObject
{
    Q_OBJECT

public:
    User(QVector<Game> games, EntryWindow* entryWindow);

    AccountType getAccountType() const;

    QString getProfilePhoto() const;

    QString getNickname() const;

    QVector<Game> getGames() const;

private:
    QString nickname;
    QString profilePhoto;
    QVector<Game> games;
    AccountType accountType = AccountType::guest;

private slots:
    void onUserLoggedIn(QString profilePhoto, QString nickname, AccountType accountType);
};

#endif // USER_H
