#include "entrywindow.h"
#include "ui_entrywindow.h"
#include <QPixmap>
#include <QIcon>
#include "game.h"
#include "Enums.h"

EntryWindow::EntryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EntryWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Foxlike Games");
    this->setWindowIcon(QIcon("../UI/Resources/Logo.ico"));

    QPixmap logoImage("../UI/Resources/Logo.png");
    ui->logo->setPixmap(logoImage.scaled(150, 150, Qt::KeepAspectRatio));
}

EntryWindow::~EntryWindow()
{
    delete ui;
}

void EntryWindow::on_continueButton_clicked()
{
    QVector<Game> games;
    User user(0, "Leon228", "Leon", games, AccountType::developer);
    emit userLoggedIn(&user);
    this->hide();
}

void EntryWindow::on_continueAsGuestButton_clicked()
{
    emit userLoggedIn(NULL);
    this->hide();
}

