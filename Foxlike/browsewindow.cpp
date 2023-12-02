#include "browsewindow.h"
#include "ui_browsewindow.h"
#include "entrywindow.h"
#include "cardcreator.h"
#include "Config.h"

BrowseWindow::BrowseWindow(QWidget *parent) : //Ask about DIP, чи не перегружений відповідальностями цей конструктор
    QMainWindow(parent),
    ui(new Ui::BrowseWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Foxlike Games");
    this->setWindowIcon(QIcon("../UI/Resources/Logo.ico"));

    CardCreator cardCreator;

    QWidget* gameCards[15];

    int counter = 0;

    for (int x = 0; x < 1; x++) {
        for (int y = 0; y < 3; y++) {
            gameCards[counter] = cardCreator.getGameCard(pathToGamesBanners + "TheWitcher3.png", "The Witcher", "The game of the world", "70 $");
            ui->GamesGrid->addWidget(gameCards[counter], x, y);
            counter++;
        }
    }

    for (int x = 1; x < 2; x++) {
        for (int y = 0; y < 3; y++) {
            gameCards[counter] = cardCreator.getGameCard(pathToGamesBanners + "TheWalkingDead.png", "The Walking Dead", "The game of the world", "30 $");
            ui->GamesGrid->addWidget(gameCards[counter], x, y);
            counter++;
        }
    }

    this->entryWindow = new EntryWindow();
    this->user = new User(entryWindow);
    this->profileWindow = new ProfileWindow(user);

    connect(entryWindow, &EntryWindow::userLoggedIn, this, &BrowseWindow::on_userLoggedIn);
    connect(profileWindow, &ProfileWindow::destroyed, this, &BrowseWindow::show);
}

BrowseWindow::~BrowseWindow()
{
    delete ui;
}

void BrowseWindow::on_accountButton_clicked()
{
    this->hide();
    if (this->user->getAccountType() != AccountType::guest) {
        this->profileWindow->show();
    }
    else {
        this->entryWindow->show();
    }
}

void BrowseWindow::on_userLoggedIn()
{
    this->show();
    delete this->profileWindow;
    this->profileWindow = new ProfileWindow(user);
}
