#include "profilewindow.h"
#include "ui_profilewindow.h"
#include "Config.h"
#include "GameCard.h"
#include <QCloseEvent>

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

    GameCard gameCard(user->getGames()[0]);
    ui->GamesScrollArea->setMinimumSize(sizeOfGameCard[0] + 50, sizeOfGameCard[1] + 20);

    ui->nicknameLabel->setText(this->user->getNickname());

    for (int x = 0; x < user->getGames().length(); x++) {
        GameCard *gameCardWidget = new GameCard(user->getGames()[0]);
        ui->GamesGrid->addWidget(gameCardWidget, x, 0);
    }
}

ProfileWindow::~ProfileWindow()
{
    delete ui;
}

void ProfileWindow::closeEvent(QCloseEvent *event)
{
    this->hide();
    emit hidden();
    event->accept();
}
