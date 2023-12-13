#ifndef BROWSEWINDOW_H
#define BROWSEWINDOW_H

#include <QMainWindow>
#include "entrywindow.h"
#include "profilewindow.h"
#include "user.h"
#include "gamesdbmanager.h"
#include "gamewindow.h"

namespace Ui {
class BrowseWindow;
}

class BrowseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BrowseWindow(QWidget *parent = nullptr); //Чи не порушується тут ISP?
    ~BrowseWindow();

public slots:
    void on_subWindowClosed();

private slots:
    void on_accountButton_clicked();
    void on_userLoggedIn();
    void createGameWindow(Game game);

    void on_FilterButton_clicked();

private:
    Ui::BrowseWindow *ui;

    GamesDBManager *dbManager;
    EntryWindow* entryWindow;
    ProfileWindow* profileWindow;
    User* user;
    GameWindow* gameWindow;

    QVector<Game> getGamesFromDBImmitation();
    void refreshGames();
};

#endif // BROWSEWINDOW_H
