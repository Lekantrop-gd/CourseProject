#include "entrywindow.h"
#include "ui_entrywindow.h"
#include "usersdbmanager.h"
#include "Config.h"
#include <QPixmap>
#include <QIcon>
#include <QMessageBox>

EntryWindow::EntryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EntryWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Foxlike Games");
    this->setWindowIcon(QIcon(pathToUIElements + "Logo.ico"));

    QPixmap logoImage(pathToUIElements + "Logo.png");
    ui->logo->setPixmap(logoImage.scaled(150, 150, Qt::KeepAspectRatio));
}

EntryWindow::~EntryWindow()
{
    delete ui;
}

void EntryWindow::on_continueButton_clicked()
{
    if (ui->nicknameInput->text() != "" && ui->passwordInput->text() != "") {
        UsersDBManager *usersDBManager = UsersDBManager::getInstance();

        User* user = usersDBManager->fetchUser(ui->nicknameInput->text(), ui->passwordInput->text());
        if (user != nullptr) {
            emit userLoggedIn(user);

            this->hide();

            ui->nicknameInput->clear();
            ui->passwordInput->clear();
        }

        else {
            QMessageBox::warning(this, "Warning!", "Nickname or password is wrong!");
        }
    }

    else {
        QMessageBox::warning(this, "Warning!", "You forgot about nickname or password.");
    }
}

void EntryWindow::on_continueAsGuestButton_clicked()
{
    User *user = new User();
    emit userLoggedIn(user);

    this->hide();

    ui->nicknameInput->clear();
    ui->passwordInput->clear();
}

