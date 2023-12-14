#include "browsewindow.h"
#include "ui_browsewindow.h"
#include "entrywindow.h"
#include "game.h"
#include "GameCard.h"
#include "Config.h"
#include "gamesdbmanager.h"
#include <QVector>
#include <QSqlDatabase>

BrowseWindow::BrowseWindow(QWidget *parent) : //Чи не перегружений відповідальностями цей конструктор
    QMainWindow(parent),
    ui(new Ui::BrowseWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Foxlike Games");
    this->setWindowIcon(QIcon("../UI/Resources/Logo.ico"));

    this->dbManager = GamesDBManager::getInstance();
    dbManager->connectToDataBase();

    refreshGames();

    ui->scrollArea->setMinimumSize(sizeOfGameCard[0] * 3 + 50, sizeOfGameCard[1] + 20);
    ui->FilterZone->hide();

    this->entryWindow = new EntryWindow();
    this->user = new User(this->dbManager->getAllGames(), entryWindow);
    this->profileWindow = new ProfileWindow(user);
    this->gameWindow = nullptr;

    connect(entryWindow, &EntryWindow::userLoggedIn, this, &BrowseWindow::on_userLoggedIn);    
}

BrowseWindow::~BrowseWindow()
{
    delete ui;
}

void BrowseWindow::refreshGames()
{
    QLayoutItem *item;
    while ((item = ui->GamesGrid->takeAt(0)) != nullptr) {
        if (QWidget *widget = item->widget()) {
            delete widget;
        }
        delete item;
    }

    QVector<Game> games = this->dbManager->getAllGames();

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

void BrowseWindow::refreshGames(QVector<Game> games)
{
    QLayoutItem *item;
    while ((item = ui->GamesGrid->takeAt(0)) != nullptr) {
        if (QWidget *widget = item->widget()) {
            delete widget;
        }
        delete item;
    }

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
    delete this->gameWindow;
    this->gameWindow = new GameWindow(game);

    connect(gameWindow, &GameWindow::hidden, this, &BrowseWindow::on_subWindowClosed);

    this->hide();
    gameWindow->show();
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
    refreshGames();
    this->show();
}

void BrowseWindow::on_FilterButton_clicked()
{
    if (ui->FilterZone->isHidden()) {
        ui->FilterZone->show();
    }
    else {
        ui->FilterZone->hide();
    }

    ui->Search->clear();
}

void BrowseWindow::on_BrowseButton_clicked()
{
    refreshGames();
    ui->Search->clear();
}

void BrowseWindow::on_Search_textChanged(const QString &arg1)
{
    if (arg1 == "") {
        refreshGames();
    }
    else {
        refreshGames(this->dbManager->getGames(arg1));
    }
}

void BrowseWindow::on_priceSlider_valueChanged(int value)
{
    if (value == 100) {
        ui->filterPriceLabel->setText("Any price");
        refreshGames();
    }
    else {
        ui->filterPriceLabel->setText("Under than " + QString::number(value));
        refreshGames(this->dbManager->getGameByPriceLoweThan(value));
    }
}

