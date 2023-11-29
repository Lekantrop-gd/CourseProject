#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H

#include <QMainWindow>
//#include "Enums.h" Why an error occures there?

namespace Ui {
class ProfileWindow;
}

class ProfileWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProfileWindow(QWidget *parent = nullptr);
    ~ProfileWindow();

private:
    Ui::ProfileWindow *ui;
    //AccountType accountType;
};

#endif // PROFILEWINDOW_H
