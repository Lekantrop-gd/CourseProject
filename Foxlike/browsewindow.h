#ifndef BROWSEWINDOW_H
#define BROWSEWINDOW_H

#include <QMainWindow>
#include "Enums.h"

namespace Ui {
class BrowseWindow;
}

class BrowseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BrowseWindow(QWidget *parent = nullptr, AccountType accountType = AccountType::guest); //Чи можна взагалі чіпати цей конструктор? Чи не порушується тут ISP?
    ~BrowseWindow();

private slots:
    void on_accountButton_clicked();

private:
    Ui::BrowseWindow *ui;
    AccountType accountType;
    QWidget* thisParent;
};

#endif // BROWSEWINDOW_H
