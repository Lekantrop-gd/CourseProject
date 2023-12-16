#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "game.h"
#include "user.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void hidden();

public:
    explicit GameWindow(Game game, User* user = nullptr, QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void on_purchaseButton_clicked();

    void on_deleteGameButton_clicked();

private:
    Ui::GameWindow *ui;

    void closeEvent(QCloseEvent *event) override;

    Game game;
    User* user;
};

#endif // GAMEWINDOW_H
