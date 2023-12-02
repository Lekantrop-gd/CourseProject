#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>
#include "entrywindow.h" //Порушення ISP

class User : public QObject
{
    Q_OBJECT

public:
    User(EntryWindow* entryWindow);

    AccountType getAccountType() const;

    QString getProfilePhoto() const;

    QString getNickname() const;

private:
    QString profilePhoto;
    QString nickname;
    AccountType accountType = AccountType::guest;
    //QVector<Game> games;

private slots:
    void onUserLoggedIn(QString profilePhoto, QString nickname, AccountType accountType);
};

#endif // USER_H
