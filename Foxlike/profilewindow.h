#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H

#include <QMainWindow>
#include "user.h"

namespace Ui {
class ProfileWindow;
}

class ProfileWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void hidden();

public:
    explicit ProfileWindow(User* user, QWidget *parent = nullptr);
    ~ProfileWindow();

private:
    Ui::ProfileWindow *ui;
    User* user;

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // PROFILEWINDOW_H
