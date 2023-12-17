#ifndef GAMEADDINGWINDOW_H
#define GAMEADDINGWINDOW_H

#include <QMainWindow>

namespace Ui {
class GameAddingWindow;
}

class GameAddingWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void gameAdded();

public:
    explicit GameAddingWindow(QWidget *parent = nullptr);
    ~GameAddingWindow();

private slots:
    void on_bannerButton_clicked();

    void on_imageButton_clicked();

    void on_logoButton_clicked();

    void on_publishGameButton_clicked();

private:
    Ui::GameAddingWindow *ui;

    QString banner;
    QString image;
    QString logo;
};

#endif // GAMEADDINGWINDOW_H
