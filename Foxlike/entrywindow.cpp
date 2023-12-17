#include "entrywindow.h"
#include "ui_entrywindow.h"
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

    this->usersDBManager = UsersDBManager::getInstance();
}

EntryWindow::~EntryWindow()
{
    delete ui;
}

void EntryWindow::on_continueButton_clicked()
{
    if (this->usersDBManager->fetchUser(ui->nicknameInput->text(), ui->passwordInput->text()) == nullptr) {
        emit userLoggedIn(nullptr);
    }
    else {
        emit userLoggedIn(this->usersDBManager->fetchUser(ui->nicknameInput->text(), ui->passwordInput->text()));
    }

    this->hide();
    ui->nicknameInput->clear();
    ui->passwordInput->clear();
}

void EntryWindow::on_continueAsGuestButton_clicked()
{
    emit userLoggedIn(nullptr);

    this->hide();
    ui->nicknameInput->clear();
    ui->passwordInput->clear();
}

