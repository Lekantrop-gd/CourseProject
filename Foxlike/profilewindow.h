#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H
#include <QMainWindow>
#include "gameaddingwindow.h"
#include "user.h"

namespace Ui {
class ProfileWindow;
}

class ProfileWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void hidden();
    void loggedOut();

public:
    explicit ProfileWindow(User* user, QWidget *parent = nullptr);
    ~ProfileWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::ProfileWindow *ui;
    GameAddingWindow* gameAddingWindow;

private slots:
    void on_gameAdded();

    void on_addGameButton_clicked();

    void on_logOutButton_clicked();
};

#endif // PROFILEWINDOW_H
