#include "gameaddingwindow.h"
#include "ui_gameaddingwindow.h"
#include "Config.h"
#include "game.h"
#include "gamesdbmanager.h"
#include <QFileDialog>
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>

GameAddingWindow::GameAddingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameAddingWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Foxlike Games");
    this->setWindowIcon(QIcon(pathToUIElements + "Logo.ico"));
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
    if (ui->bannerHandler->pixmap().isNull() ||
        ui->imageHabdler->pixmap().isNull() ||
        ui->shortDescriptionInput->text().length() < 20 ||
        ui->fullDescriptionInput->toPlainText().length() < 100 ||
        ui->logoHandler->pixmap().isNull() ||
        ui->titleInput->text().length() < 1 ||
        ui->developerInput->text().length() < 1 ||
        ui->publisherInput->text().length() < 1 ||
        ui->releaseDateInput->text().length() < 3 ||
        ui->genreInput->text().length() < 1||
        ui->priceInput->text().length() < 1)
    {
        QMessageBox::warning(this, "Warning!", "You haven't filled all fields or met the minimum number of characters.");
    }
    else
    {
        GamesDBManager *dbManager = GamesDBManager::getInstance();

        Game game(
            0,
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

        if (!dbManager->inserGameIntoTable(game)) {
            QMessageBox::warning(this, "Warning!", "Unable to add game. Try later or change title or short/full description, it might cause the problem.");
        }

        QFile::copy(this->banner, pathToGamesImages + QFileInfo(this->banner).fileName());
        QFile::copy(this->image, pathToGamesImages + QFileInfo(this->image).fileName());
        QFile::copy(this->logo, pathToGamesImages + QFileInfo(this->logo).fileName());

        emit gameAdded();
    }
}

void GameAddingWindow::closeEvent(QCloseEvent *event)
{
    emit hidden();
    event->accept();
}
