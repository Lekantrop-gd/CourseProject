#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "Config.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include "gamesdbmanager.h"
#include "purchasedgamesdbmanager.h"

GameWindow::GameWindow(Game game, User* user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow),
    game(game),
    user(user)
{
    ui->setupUi(this);

    this->setWindowTitle("Foxlike Games");
    this->setWindowIcon(QIcon(pathToUIElements + "Logo.ico"));
    
    ui->gameImageHandel->setPixmap(QPixmap(pathToGamesImages + game.getImage()));
    ui->logoLabel->setPixmap(QPixmap(pathToGamesImages + game.getIcon()));

    ui->titleLabel->setText(game.getTitle());
    ui->descriptionTextBrowser->setText(game.getFullDescription());
    ui->developerLabel->setText(ui->developerLabel->text() + game.getDeveloper());
    ui->publisherLabel->setText(ui->publisherLabel->text() + game.getPublisher());
    ui->releaseDateLabel->setText(ui->releaseDateLabel->text() + game.getReleaseDate());
    ui->genreLabel->setText(ui->genreLabel->text() + game.getGenre());

    QString price;
    if (game.getPrice() == 0) price = "Free";
    else price = QString::number(game.getPrice(), 'f', 2) + "$";

    ui->priceLabel->setText(price);
    ui->descriptionTextBrowser->setTextInteractionFlags(Qt::NoTextInteraction);
    
    if (user->getAccountType() != AccountType::contentManager) {
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
    else {
        PurchasedGamesDBManager *purchasedGamesDBManager = PurchasedGamesDBManager::getInstance();

        QMessageBox::information(this, "Payment", "In order to purchase the game, "
                                       "you need to pay for it using the "
                                       "card number: **************** and "
                                       "upload a screenshot of the payment");


        QString filePath = QFileDialog::getOpenFileName(nullptr, "Select payment screenshot", QDir::homePath(), "Images(*.jpg, *.jpeg, *.png)");

        if (filePath.isEmpty()) {
            QMessageBox::warning(this, "Warning!", "Select a payment screenshot!");
            return;
        }

        QFile::copy(filePath, pathToPayments + QString::number(this->user->getId()) +
                                               QString::number(this->game.getId()));

        if (purchasedGamesDBManager->addPurchase(this->user->getId(),
                                                 this->game.getId(),
                                                 QString::number(this->user->getId()) +
                                                 QString::number(this->game.getId())))
        {
            QMessageBox::information(this, "Congratulation!", "You bought this game! It will appear in your accont when admin confirms it.");
        }
        else {
            QMessageBox::warning(this, "Warning!", "Something went wrong. You could already have this game or "
                                                   "problems with database may occure. Please try later.");
        }
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

        if (!dbManager->deleteGame(this->game.getId())) {
            QMessageBox::warning(this, "Warning!", "Unable to delete game. Try later or contact the administration");
        }

        this->close();
    }
}

