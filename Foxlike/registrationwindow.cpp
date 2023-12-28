#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include "Config.h"
#include "user.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QFileDialog>

RegistrationWindow::RegistrationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Foxlike Games");
    this->setWindowIcon(QIcon(pathToUIElements + "Logo.ico"));

    QPixmap logoImage(pathToUIElements + "Logo.png");
    ui->logo->setPixmap(logoImage.scaled(150, 150, Qt::KeepAspectRatio));

    this->userDBM = UsersDBManager::getInstance();

    QVector<QString> accountTypes = userDBM->getAccountTypes();

    for (QString accountType : accountTypes) {
        ui->accountTypesComboBox->addItem(accountType);
    }
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::on_continueButton_clicked()
{
    if (!ui->nicknameInput->text().isEmpty() &&
        !ui->nicknameInput->text().isEmpty() &&
        !this->profilePhoto.isEmpty())
    {
        AccountType accountType;

        if (ui->accountTypesComboBox->currentIndex() == 1) accountType = AccountType::developer;
        if (ui->accountTypesComboBox->currentIndex() == 0) accountType = AccountType::contentManager;
        else accountType = AccountType::user;

        QVector<Game> games;  

        User user(0,
                  ui->nicknameInput->text(),
                  ui->nicknameInput->text().remove(QChar(' ')),
                  games,
                  accountType);

        UsersDBManager *userDBM = UsersDBManager::getInstance();

        if (userDBM->insertUserIntoTable(user, ui->passwordInput->text())) {
            QFile::copy(this->profilePhoto, pathToProfilesImages + ui->nicknameInput->text().remove(QChar(' ')));

            QMessageBox::information(this, "Congratulations!", "You'he registered your account! Now wait until administration approve it");

            this->close();
            return;
        }

        QMessageBox::critical(this, "Error", "Something went wrong with database... Try again later");
    }
    else {
        QMessageBox::warning(this, "Error", "Input all fields");
    }
}

void RegistrationWindow::closeEvent(QCloseEvent *event)
{
    emit hidden();
    event->accept();
}


void RegistrationWindow::on_photoButton_clicked()
{
    QString photo = QFileDialog::getOpenFileName(nullptr, "Select your photo", QDir::homePath(), "Images(*.jpg, *.jpeg, *.jpe *.jif, *.jfif, *.jfi, *.png)");

    this->profilePhoto = photo;

    ui->logo->setPixmap(QPixmap(photo));
}
