#include "browsewindow.h"
#include "ui_browsewindow.h"

BrowseWindow::BrowseWindow(QWidget *parent, AccountType accountType) : //Ask about DIP
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
            gameCards[counter] = cardCreator.getGameCard("../UI/Resources/Witcher.png", "The Witcher", "The game of the world", "70 $");
            ui->GamesGrid->addWidget(gameCards[counter], x, y);
            counter++;
        }
    }

    for (int x = 1; x < 2; x++) {
        for (int y = 0; y < 3; y++) {
            gameCards[counter] = cardCreator.getGameCard("../UI/Resources/TheWalkingDead.png", "The Walking Dead", "The game of the world", "30 $");
            ui->GamesGrid->addWidget(gameCards[counter], x, y);
            counter++;
        }
    }
}

BrowseWindow::~BrowseWindow()
{
    delete ui;
}
