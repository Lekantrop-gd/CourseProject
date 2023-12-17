#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H
#include <QMainWindow>
#include "user.h"
#include "usersdbmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EntryWindow; }
QT_END_NAMESPACE

class EntryWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void userLoggedIn(User* user);

public:
    EntryWindow(QWidget *parent = nullptr);
    ~EntryWindow();

private slots:
    void on_continueButton_clicked();

    void on_continueAsGuestButton_clicked();

private:
    Ui::EntryWindow *ui;
    UsersDBManager *usersDBManager;
};
#endif // ENTRYWINDOW_H
