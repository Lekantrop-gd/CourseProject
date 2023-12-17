#include "browsewindow.h"
#include "ui_browsewindow.h"
#include "entrywindow.h"
#include "game.h"
#include "GameCard.h"
#include "Config.h"
#include "gamesdbmanager.h"
#include "mysqldbmanager.h"
#include <QVector>
#include <QSqlDatabase>

BrowseWindow::BrowseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BrowseWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Foxlike Games");
    this->setWindowIcon(QIcon("../UI/Resources/Logo.ico"));

    MySQLDBManager *mySQLDBManager = MySQLDBManager::getInstance();
    mySQLDBManager->connectToDataBase();
    mySQLDBManager->createTables();

    this->dbManager = GamesDBManager::getInstance();

    refreshGames(this->dbManager->getAllGames());

    ui->scrollArea->setMinimumSize(sizeOfGameCard[0] * 3 + 50, sizeOfGameCard[1] + 20);
    ui->filterButtons->hide();

    this->entryWindow = new EntryWindow();
    this->user = new User();
    this->profileWindow = new ProfileWindow(nullptr);
    this->gameWindow = nullptr;

    connect(entryWindow, &EntryWindow::userLoggedIn, this, &BrowseWindow::on_userLoggedIn);    
}

BrowseWindow::~BrowseWindow()
{
    delete ui;
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
        connect(gameCards[counter], &GameCard::clicked, this, &BrowseWindow::on_gameWindowClicked);

        if (y >= gamesGridNumberOfColumns) { y = 0; x++; }

        ui->GamesGrid->addWidget(gameCards[counter], x, y);

        y++; counter++;
    }
}

void BrowseWindow::on_gameWindowClicked(Game game)
{
    delete this->gameWindow;
    this->gameWindow = new GameWindow(game, this->user);

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

void BrowseWindow::on_userLoggedIn(User* user)
{
    delete this->profileWindow;
    delete this->user;

    if (user != nullptr) {
        this->user = new User(user);
        this->profileWindow = new ProfileWindow(this->user);
    }
    else {
        this->profileWindow = new ProfileWindow(nullptr);
    }

    connect(profileWindow, &ProfileWindow::hidden, this, &BrowseWindow::on_subWindowClosed);
    connect(profileWindow, &ProfileWindow::loggedOut, this, &BrowseWindow::on_userLoggedOut);

    this->show();
}

void BrowseWindow::on_userLoggedOut()
{
    delete this->user;
    this->user = new User();
}

void BrowseWindow::on_subWindowClosed()
{
    refreshGames(this->dbManager->getAllGames());

    this->show();
}

void BrowseWindow::on_search_textChanged(const QString &arg1)
{
    ui->filterButtons->hide();
    refreshGames(this->dbManager->getGamesByKeyWords(arg1));
}

void BrowseWindow::on_filterButton_clicked()
{
    if (ui->filterButtons->isHidden()) {
        ui->search->setText("");
        ui->filterButtons->show();
    }
    else {
        ui->filterButtons->hide();
    }
}

void BrowseWindow::on_priceSlider_valueChanged(int value)
{
    ui->genreComboBox->setCurrentIndex(0);

    if (value == 100) {
        ui->priceText->setText("Any price");
        refreshGames(this->dbManager->getAllGames());
    }
    else {
        ui->priceText->setText("Under " + QString::number(value) + "$");
        refreshGames(this->dbManager->getGamesByPrice(value));
    }
}

void BrowseWindow::on_browseButton_clicked()
{
    ui->filterButtons->hide();
    ui->search->clear();
    refreshGames(this->dbManager->getAllGames());
}

void BrowseWindow::on_genreComboBox_textActivated(const QString &arg1)
{
    ui->priceSlider->setSliderPosition(100);

    if (arg1 == "None") {
        refreshGames(this->dbManager->getAllGames());
    }
    else {
        refreshGames(this->dbManager->getGamesByGenre(arg1));
    }
}
