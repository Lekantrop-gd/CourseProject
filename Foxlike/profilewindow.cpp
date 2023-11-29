#include "profilewindow.h"
#include "ui_profilewindow.h"

ProfileWindow::ProfileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProfileWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Foxlike Games");
    this->setWindowIcon(QIcon("../UI/Resources/Logo.ico"));
}

ProfileWindow::~ProfileWindow()
{
    delete ui;
}
