#include "gameaddingwindow.h"
#include "ui_gameaddingwindow.h"
#include "Config.h"
#include "game.h"
#include "gamesdbmanager.h"
#include <QFileDialog>
#include <QDebug>

GameAddingWindow::GameAddingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameAddingWindow)
{
    ui->setupUi(this);
}

GameAddingWindow::~GameAddingWindow()
{
    delete ui;
}

void GameAddingWindow::on_bannerButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Select game banner", QDir::homePath(), "Images (*.jpg)");

    this->banner = filePath;

    ui->bannerHandler->setPixmap(QPixmap(filePath));
}


void GameAddingWindow::on_imageButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Select game image", QDir::homePath(), "Images (*.jpg)");

    this->image = filePath;

    ui->imageHabdler->setPixmap(QPixmap(filePath));
}


void GameAddingWindow::on_logoButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Select game logo", QDir::homePath(), "Images (*.png)");

    this->logo = filePath;

    ui->logoHandler->setPixmap(QPixmap(filePath));
}

void GameAddingWindow::on_publishGameButton_clicked()
{
    GamesDBManager *dbManager = GamesDBManager::getInstance();

    QFile::copy(this->banner, pathToGamesBanners + QFileInfo(this->banner).fileName() + gameBannersExtension);
    QFile::copy(this->image, pathToGamesBanners + QFileInfo(this->image).fileName() + gameBannersExtension);
    QFile::copy(this->logo, pathToGamesBanners + QFileInfo(this->logo).fileName() + gameLogosExtension);

    Game game(
        dbManager->getLastGameId() + 1,
        ui->titleInput->text(),
        ui->shortDescriptionInput->text(),
        ui->fullDescriptionInput->toPlainText(),
        ui->priceInput->text().toFloat(),
        ui->developerInput->text(),
        ui->publisherInput->text(),
        ui->releaseDateInput->text(),
        ui->genreInput->text(),
        QFileInfo(this->banner).fileName(),
        QFileInfo(this->image).fileName(),
        QFileInfo(this->logo).fileName()
        );

    dbManager->inserGameIntoTable(game);

    delete dbManager;
}

