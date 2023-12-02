#include "profilewindow.h"
#include "ui_profilewindow.h"
#include "Config.h"

ProfileWindow::ProfileWindow(User* user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProfileWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Foxlike Games");
    this->setWindowIcon(QIcon("../UI/Resources/Logo.ico"));

    this->user = user;

    ui->profilePhoto->setPixmap(QPixmap(pathToProfilesImages + this->user->getProfilePhoto() + profilePhotosExtension));
    ui->profilePhoto->setMinimumSize(200, 200);

    ui->nicknameLabel->setText(this->user->getNickname());
}

ProfileWindow::~ProfileWindow()
{
    delete ui;
}
