#include "profilewindow.h"
#include "ui_profilewindow.h"

ProfileWindow::ProfileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProfileWindow)
{
    ui->setupUi(this);
}

ProfileWindow::~ProfileWindow()
{
    delete ui;
}
