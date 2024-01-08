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
#include <QMessageBox>
#include <QDesktopServices>
#include <QDir>

BrowseWindow::BrowseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BrowseWindow)
{
    ui->setupUi(this);
    
    MySQLDBManager *mySQLDBManager = MySQLDBManager::getInstance();
    this->dbManager = GamesDBManager::getInstance();

    if (!mySQLDBManager->connectToDataBase()) {
        QMessageBox::warning(this, "Fatal error", "Unable to connect to database. Try again later", QMessageBox::Ok);
        QCoreApplication::quit();
    }

    mySQLDBManager->createTables();

    this->setWindowTitle("Foxlike Games");
    this->setWindowIcon(QIcon(pathToUIElements + "Logo.ico"));

    ui->scrollArea->setMinimumSize(sizeOfGameCard[0] * 3 + 50, sizeOfGameCard[1] + 20);
    ui->filterButtons->hide();

    ui->genreComboBox->addItem("None");
    for (QString genre : dbManager->getAllGenres()) {
        ui->genreComboBox->addItem(genre);
    }

    refreshGames(this->dbManager->getAllGames());

    this->entryWindow = new EntryWindow();
    this->user = new User();
    this->profileWindow = new ProfileWindow(nullptr);
    this->gameWindow = nullptr;

    connect(entryWindow, &EntryWindow::userLoggedIn, this, &BrowseWindow::on_userLoggedIn);
    connect(entryWindow, &EntryWindow::hidden, this, &BrowseWindow::on_subWindowClosed);
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
        connect(gameCards[counter], &GameCard::clicked, this, &BrowseWindow::on_gameCardClicked);

        if (y >= gamesGridNumberOfColumns) { y = 0; x++; }

        ui->GamesGrid->addWidget(gameCards[counter], x, y);

        y++; counter++;
    }
}

void BrowseWindow::on_gameCardClicked(Game game)
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
        this->profileWindow->refreshGames();
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
        this->user = nullptr;
        this->profileWindow = new ProfileWindow(nullptr);
    }

    connect(profileWindow, &ProfileWindow::hidden, this, &BrowseWindow::on_subWindowClosed);
    connect(profileWindow, &ProfileWindow::loggedOut, this, &BrowseWindow::on_userLoggedOut);

    on_subWindowClosed();
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
    ui->priceSlider->setSliderPosition(ui->priceSlider->maximum());
    ui->genreComboBox->setCurrentIndex(0);

    ui->filterButtons->hide();

    refreshGames(this->dbManager->getGamesByKeyWords(arg1));
}

void BrowseWindow::on_filterButton_clicked()
{
    if (ui->filterButtons->isHidden()) {
        ui->search->clear();
        ui->filterButtons->show();
    }
    else {
        ui->filterButtons->hide();
    }
}

void BrowseWindow::on_genreComboBox_textActivated(const QString &arg1)
{
    ui->priceSlider->setSliderPosition(ui->priceSlider->maximum());

    if (arg1 == ui->genreComboBox->itemText(0)) {
        refreshGames(this->dbManager->getAllGames());
    }
    else {
        refreshGames(this->dbManager->getGamesByGenre(arg1));
    }
}

void BrowseWindow::on_priceSlider_valueChanged(int value)
{
    ui->genreComboBox->setCurrentIndex(0);

    if (value == ui->priceSlider->maximum()) {
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
