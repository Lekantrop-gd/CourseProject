#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "Config.h"
#include <QMouseEvent>
#include <QMessageBox>
#include "gamesdbmanager.h"

GameWindow::GameWindow(Game game, User* user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow),
    game(game),
    user(user)
{
    ui->setupUi(this);

    this->setWindowTitle("Foxlike Games");
    this->setWindowIcon(QIcon("../UI/Resources/Logo.ico"));

    ui->gameImageHandel->setPixmap(QPixmap(pathToGamesBanners + game.getImage() + gameBannersExtension));
    ui->logoLabel->setPixmap(QPixmap(pathToGamesBanners + game.getIcon() + gameLogosExtension));

    ui->titleLabel->setText(game.getTitle());
    ui->descriptionTextBrowser->setText(game.getFullDescription());
    ui->developerLabel->setText(ui->developerLabel->text() + game.getDeveloper());
    ui->publisherLabel->setText(ui->publisherLabel->text() + game.getPublisher());
    ui->releaseDateLabel->setText(ui->releaseDateLabel->text() + game.getReleaseDate());
    ui->genreLabel->setText(ui->genreLabel->text() + game.getGenre());
    ui->priceLabel->setText(QString::number(game.getPrice(), 'f', 2) + "$");
    ui->descriptionTextBrowser->setTextInteractionFlags(Qt::NoTextInteraction);

    if (user->getAccountType() != AccountType::admin) {
        ui->deleteGameButton->hide();
    }
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::closeEvent(QCloseEvent *event)
{
    this->hide();
    emit hidden();
    event->accept();
}

void GameWindow::on_purchaseButton_clicked()
{
    if (user->getAccountType() == AccountType::guest) {
        QMessageBox::critical(this, "Purchase error", "Unable to make a purchase. Log in first.");
    }
}

void GameWindow::on_deleteGameButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
        this,
        "Confirmation",
        "Are you sure you want to delete this game?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        GamesDBManager *dbManager = GamesDBManager::getInstance();
        dbManager->deleteGame(this->game.getId());
        delete dbManager; //What i have to do with that?
        this->close();
    }
}

