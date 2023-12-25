#include "entrywindow.h"
#include "ui_entrywindow.h"
#include "usersdbmanager.h"
#include "registrationwindow.h"
#include "Config.h"
#include <QFileDialog>
#include <QPixmap>
#include <QIcon>
#include <QMessageBox>
#include <QCloseEvent>

EntryWindow::EntryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EntryWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Foxlike Games");
    this->setWindowIcon(QIcon(pathToUIElements + "Logo.ico"));

    QPixmap logoImage(pathToUIElements + "Logo.png");
    ui->logo->setPixmap(logoImage.scaled(150, 150, Qt::KeepAspectRatio));

    this->registrationWindow = new RegistrationWindow();
    connect(registrationWindow, &RegistrationWindow::hidden, this, &EntryWindow::show);
}

EntryWindow::~EntryWindow()
{
    delete ui;
}

void EntryWindow::on_continueButton_clicked()
{
    if (ui->nicknameInput->text().isEmpty() == false && ui->passwordInput->text().isEmpty() == false) {
        UsersDBManager *usersDBManager = UsersDBManager::getInstance();

        if (usersDBManager->checkIfUserExists(ui->nicknameInput->text())) {
            User* user = usersDBManager->fetchUser(ui->nicknameInput->text(), ui->passwordInput->text());

            if (user != nullptr) {
                emit userLoggedIn(user);

                this->hide();

                ui->nicknameInput->clear();
                ui->passwordInput->clear();
            }
            else {
                QMessageBox::warning(this, "Warning!", "Password is wrong!");
            }
        }
        else {
            QMessageBox::warning(this, "Warning!", "There is no account with that username!");
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

void EntryWindow::on_continueButton_2_clicked()
{
    registrationWindow->show();
    this->hide();
}

void EntryWindow::closeEvent(QCloseEvent *event)
{
    emit hidden();
    event->accept();
}

