#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "game.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void hidden();

public:
    explicit GameWindow(Game game, QWidget *parent = nullptr);
    ~GameWindow();

private:
    Ui::GameWindow *ui;

    void closeEvent(QCloseEvent *event) override;
};

#endif // GAMEWINDOW_H
