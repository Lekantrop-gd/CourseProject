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

public slots:
    void on_subWindowClosed();

private slots:
    void on_accountButton_clicked();
    void on_userLoggedIn();
    void createGameWindow(Game game);

private:
    Ui::BrowseWindow *ui;

    EntryWindow* entryWindow;
    ProfileWindow* profileWindow;
    User* user;

    QVector<Game> getGamesFromDBImmitation();
    void refreshGames(QVector<Game> games);
};

#endif // BROWSEWINDOW_H
