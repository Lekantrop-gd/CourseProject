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

private:
    QString login;
    QString balance;
    AccountType accountType = AccountType::guest;

private slots:
    void onUserLoggedIn(QString login, QString balance, AccountType accountType);
};

#endif // USER_H
