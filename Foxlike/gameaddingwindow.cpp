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
    if (ui->bannerHandler->pixmap().isNull()) {
        QMessageBox::warning(this, "Warning!", "You did't upload game banner!");
        return;
    }

    if (ui->imageHabdler->pixmap().isNull()) {
        QMessageBox::warning(this, "Warning!", "You did't upload game image!");
        return;
    }

    if (ui->logoHandler->pixmap().isNull()) {
        QMessageBox::warning(this, "Warning!", "You did't upload game logo!");
        return;
    }

    if (ui->shortDescriptionInput->text().length() < 20) {
        QMessageBox::warning(this, "Warning!", "Minimum required lenght for short description is 20 characters!");
        return;
    }
    if (ui->fullDescriptionInput->toPlainText().length() < 100) {
        QMessageBox::warning(this, "Warning!", "Minimum required lenght for full description is 100 characters!");
        return;
    }

    if (ui->titleInput->text().length() < 1) {
        QMessageBox::warning(this, "Warning!", "Minimum required lenght for title is 1 character!");
        return;
    }

    if (ui->developerInput->text().length() < 1) {
        QMessageBox::warning(this, "Warning!", "Minimum required lenght for developer is 1 character!");
        return;
    }

    if (ui->publisherInput->text().length() < 1) {
        QMessageBox::warning(this, "Warning!", "Minimum required lenght for publisher is 1 character!");
        return;
    }

    if (!ui->priceInput->text().toFloat()) {
        QMessageBox::warning(this, "Warning!", "Price can't be a string!");
        return;
    }

    else {
        if (ui->priceInput->text().toFloat() < 0 || ui->priceInput->text().toFloat() > 100) {
            QMessageBox::warning(this, "Warning!", "Price can't lower than 0$ or greater than 100$!");
            return;
        }
    }

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
        ui->titleInput->text().remove(QChar(' ')) + QString::number(1),
        ui->titleInput->text().remove(QChar(' ')) + QString::number(2),
        ui->titleInput->text().remove(QChar(' ')) + QString::number(3)
        );

    if (!dbManager->inserGameIntoTable(game)) {
        QMessageBox::warning(this, "Warning!", "Unable to add game. Try later or change title or short/full description, it might cause the problem.");
        return;
    }

    QMessageBox::information(this, "Congratulations!", "You'he added your game! Now wait until administration approve it");

    QFile::copy(this->banner, pathToGamesImages + ui->titleInput->text().remove(QChar(' ')) + QString::number(1));
    QFile::copy(this->image, pathToGamesImages + ui->titleInput->text().remove(QChar(' ')) + QString::number(2));
    QFile::copy(this->logo, pathToGamesImages + ui->titleInput->text().remove(QChar(' ')) + QString::number(3));

    emit gameAdded();
}

void GameAddingWindow::closeEvent(QCloseEvent *event)
{
    emit hidden();
    event->accept();
}
