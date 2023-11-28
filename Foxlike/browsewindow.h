#ifndef BROWSEWINDOW_H
#define BROWSEWINDOW_H

#include <QMainWindow>
#include "cardcreator.h"
#include "Enums.h"

namespace Ui {
class BrowseWindow;
}

class BrowseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BrowseWindow(QWidget *parent = nullptr, AccountType accountType = AccountType::guest);
    ~BrowseWindow();

private:
    Ui::BrowseWindow *ui;
};

#endif // BROWSEWINDOW_H
