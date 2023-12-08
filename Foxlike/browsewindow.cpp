#include "browsewindow.h"
#include "ui_browsewindow.h"
#include "entrywindow.h"
#include "cardcreator.h"
#include "game.h"
#include "gamewindow.h"
#include <QVector>

BrowseWindow::BrowseWindow(QWidget *parent) : //Чи не перегружений відповідальностями цей конструктор
    QMainWindow(parent),
    ui(new Ui::BrowseWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Foxlike Games");
    this->setWindowIcon(QIcon("../UI/Resources/Logo.ico"));

    CardCreator cardCreator;

    Game game(1,
              "The Witcher 3: Wild Hunt",
              "The best game in the world",
              "I'm too lazy to write a text this long.",
              100,
              "CDRP",
              "CDPR Ineractive",
              "01.01.2015",
              "RPG",
              "1",
              "11",
              "111");

    QWidget* gameCards[15];

    int counter = 0;
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 3; y++) {
            gameCards[counter] = cardCreator.getGameCard(game);
            ui->GamesGrid->addWidget(gameCards[counter], x, y);
            counter++;
        }
    }

    this->entryWindow = new EntryWindow();
    this->user = new User(entryWindow);
    this->profileWindow = new ProfileWindow(user);

    connect(entryWindow, &EntryWindow::userLoggedIn, this, &BrowseWindow::on_userLoggedIn);
    connect(profileWindow, &ProfileWindow::destroyed, this, &BrowseWindow::show);

    GameWindow *gameWindow = new GameWindow(game);
    gameWindow->show();

    this->hide();
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
