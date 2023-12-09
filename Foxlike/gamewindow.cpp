#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "Config.h"

GameWindow::GameWindow(Game game, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    ui->descriptionTextBrowser->setTextInteractionFlags(Qt::NoTextInteraction);

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
    ui->priceLabel->setText(QString::number(game.getPrice()) + "$");
}

GameWindow::~GameWindow()
{
    delete ui;
}
