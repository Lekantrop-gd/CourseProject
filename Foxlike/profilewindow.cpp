#include "profilewindow.h"
#include "ui_profilewindow.h"
#include "Config.h"
#include "cardcreator.h"
#include <QCloseEvent>

ProfileWindow::ProfileWindow(User* user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProfileWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Foxlike Games");
    this->setWindowIcon(QIcon("../UI/Resources/Logo.ico"));

    this->user = user;

    CardCreator cardCreator;

    ui->profilePhoto->setPixmap(QPixmap(pathToProfilesImages + this->user->getProfilePhoto() + profilePhotosExtension));
    ui->profilePhoto->setMinimumSize(200, 200);

    ui->GamesScrollArea->setMinimumSize(cardCreator.getGameCard(user->getGames()[0])->width() + 50,
                                        cardCreator.getGameCard(user->getGames()[0])->height() + 20);

    QWidget* gameCards[5];

    ui->nicknameLabel->setText(this->user->getNickname());
    for (int x = 0; x < user->getGames().length(); x++) {
        gameCards[x] = cardCreator.getGameCard(user->getGames()[x]);
        ui->GamesGrid->addWidget(gameCards[x], x, 0);
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
