#include "user.h"
#include <QDebug>

User::User(EntryWindow *entryWindow)
{
    connect(entryWindow, &EntryWindow::userLoggedIn, this, &User::onUserLoggedIn);
}

AccountType User::getAccountType() const
{
    return accountType;
}

void User::onUserLoggedIn(QString login, QString balance, AccountType accountType)
{
    this->login = login;
    this->balance = balance;
    this->accountType = accountType;
    qInfo() << login + " " + balance;
}
