#ifndef BROWSEWINDOW_H
#define BROWSEWINDOW_H

#include <QMainWindow>
#include "entrywindow.h"
#include "profilewindow.h"
#include "user.h"

namespace Ui {
class BrowseWindow;
}

class BrowseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BrowseWindow(QWidget *parent = nullptr); //Чи не порушується тут ISP?
    ~BrowseWindow();

private slots:
    void on_accountButton_clicked();
    void onAccountLoggedIn(AccountType accountType);

private:
    Ui::BrowseWindow *ui;

    EntryWindow* entryWindow;
    ProfileWindow* profileWindow;
    User* user;
};

#endif // BROWSEWINDOW_H
