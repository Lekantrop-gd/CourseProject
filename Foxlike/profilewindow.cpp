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

    ui->GamesScrollArea->setMinimumSize(sizeOfGameCard[0] + 50, sizeOfGameCard[1] + 20);

    ui->nicknameLabel->setText(this->user->getNickname());

    if (this->user->getAccountType() != AccountType::developer) {
        ui->addGameButton->hide();
    }

    if (this->user->getAccountType() != AccountType::guest) {
        int counter = 0;
        for (Game game : user->getGames()) {
            GameCard *gameCardWidget = new GameCard(game);
            ui->GamesGrid->addWidget(gameCardWidget, counter, 0);
            counter++;
        }
    }
}

ProfileWindow::~ProfileWindow()
{
    delete ui;
}

void ProfileWindow::on_gameAdded()
{
    delete this->gameAddingWindow;
    this->close();
}

void ProfileWindow::closeEvent(QCloseEvent *event)
{
    emit hidden();
    event->accept();
}

void ProfileWindow::on_addGameButton_clicked()
{
    this->gameAddingWindow = new GameAddingWindow(this);

    connect(this->gameAddingWindow, &GameAddingWindow::gameAdded, this, &ProfileWindow::on_gameAdded);

    this->hide();

    gameAddingWindow->show();
}

