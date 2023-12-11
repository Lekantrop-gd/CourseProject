#include "browsewindow.h"
#include "ui_browsewindow.h"
#include "entrywindow.h"
#include "cardcreator.h"
#include "game.h"
#include "gamewindow.h"
#include <QPushButton>
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

    QVector<Game> games;
    games.push_back(game);
    games.push_back(game);
    games.push_back(game);
    games.push_back(game);
    games.push_back(game);

    QWidget* gameCards[15];

    for (int x = 0; x < 6; x++) {
        for (int y = 0; y < 3; y++) {
            gameCards[0] = cardCreator.getGameCard(game);
            connect(gameCards[0], &QWidget::cursor, this, &BrowseWindow::on_accountButton_clicked);
            ui->GamesGrid->addWidget(gameCards[0], x, y);
        }
    }

    this->entryWindow = new EntryWindow();
    this->user = new User(games, entryWindow);
    this->profileWindow = new ProfileWindow(user);

    connect(entryWindow, &EntryWindow::userLoggedIn, this, &BrowseWindow::on_userLoggedIn);

    ui->scrollArea->setMinimumSize(gameCards[0]->width() * 3 + 50, gameCards[0]->height() + 20);
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
