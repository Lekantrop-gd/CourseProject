#include "entrywindow.h"
#include "ui_entrywindow.h"
#include "browsewindow.h"
#include <QPixmap>
#include <QIcon>

EntryWindow::EntryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EntryWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Foxlike Games");
    this->setWindowIcon(QIcon("../UI/Resources/Logo.ico"));

    QPixmap logoImage("../UI/Resources/Logo.png");
    ui->logo->setPixmap(logoImage.scaled(150, 150, Qt::KeepAspectRatio));
}

EntryWindow::~EntryWindow()
{
    delete ui;
}

void EntryWindow::on_continueButton_clicked()
{

}

void EntryWindow::on_continueAsGuestButton_clicked()
{
    BrowseWindow *browseWindow = new BrowseWindow(this, AccountType::user);
    browseWindow->show();
    this->hide();
}

