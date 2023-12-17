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
    explicit BrowseWindow(QWidget *parent = nullptr);
    ~BrowseWindow();

public slots:
    void on_subWindowClosed();

private slots:
    void on_accountButton_clicked();

    void on_userLoggedIn(User user);

    void on_gameWindowClicked(Game game);

    void on_search_textChanged(const QString &arg1);

    void on_filterButton_clicked();

    void on_priceSlider_valueChanged(int value);

    void on_browseButton_clicked();

    void on_genreComboBox_textActivated(const QString &arg1);

private:
    Ui::BrowseWindow *ui;

    GamesDBManager *dbManager;
    EntryWindow* entryWindow;
    ProfileWindow* profileWindow;
    User* user;
    GameWindow* gameWindow;

    void refreshGames(QVector<Game> games);
};

#endif // BROWSEWINDOW_H
