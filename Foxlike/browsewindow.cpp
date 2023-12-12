#include "browsewindow.h"
#include "ui_browsewindow.h"
#include "entrywindow.h"
#include "game.h"
#include "GameCard.h"
#include "Config.h"
#include "gamewindow.h"
#include <QPushButton>
#include <QVector>

BrowseWindow::BrowseWindow(QWidget *parent) : //Чи не перегружений відповідальностями цей конструктор
    QMainWindow(parent),
    ui(new Ui::BrowseWindow)
{
    ui->setupUi(this);

    //Repeats in every form class
    this->setWindowTitle("Foxlike Games");
    this->setWindowIcon(QIcon("../UI/Resources/Logo.ico"));
    //Should be remover

    QVector<Game> games = getGamesFromDBImmitation();
    refreshGames(games);

    ui->scrollArea->setMinimumSize(sizeOfGameCard[0] * 3 + 50, sizeOfGameCard[1] + 20);

    this->entryWindow = new EntryWindow();
    this->user = new User(games, entryWindow);
    this->profileWindow = new ProfileWindow(user);

    connect(entryWindow, &EntryWindow::userLoggedIn, this, &BrowseWindow::on_userLoggedIn);    
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
    delete this->profileWindow;
    this->profileWindow = new ProfileWindow(user);

    connect(profileWindow, &ProfileWindow::hidden, this, &BrowseWindow::on_userLoggedIn);

    this->show();
}

void BrowseWindow::on_subWindowClosed()
{
    QVector<Game> games = getGamesFromDBImmitation();
    refreshGames(games);
    this->show();
}

QVector<Game> BrowseWindow::getGamesFromDBImmitation()
{
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

    QVector<Game> games;
    for (int x = 0; x < 100; x++) {
        games.push_back(game);
    }

    return games;
}

void BrowseWindow::refreshGames(QVector<Game> games)
{
    GameCard* gameCards[games.size()];

    int counter = 0;
    int x = 0;
    int y = 0;

    for (Game game : games) {
        gameCards[counter] = new GameCard(games[counter]);
        connect(gameCards[counter], &GameCard::clicked, this, &BrowseWindow::createGameWindow);

        if (y >= gamesGridNumberOfColumns) { y = 0; x++; }

        ui->GamesGrid->addWidget(gameCards[counter], x, y);

        y++; counter++;
    }
}

void BrowseWindow::createGameWindow(Game game)
{
    GameWindow* gameWindow = new GameWindow(game);
    connect(gameWindow, &GameWindow::hidden, this, &BrowseWindow::on_subWindowClosed);
    this->hide();
    gameWindow->show();
}
