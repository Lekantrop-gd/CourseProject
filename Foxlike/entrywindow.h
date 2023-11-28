#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class EntryWindow; }
QT_END_NAMESPACE

class EntryWindow : public QMainWindow
{
    Q_OBJECT

public:
    EntryWindow(QWidget *parent = nullptr);
    ~EntryWindow();

private slots:
    void on_continueButton_clicked();

    void on_continueAsGuestButton_clicked();

private:
    Ui::EntryWindow *ui;
    const int DEFAULT_WINDOW_WIDTH = 1280;
    const int DEFAULT_WINDOW_HEIGHT = 720;
    const QString STYLE_SHEET = "QMainWindow {"
                                "   background-color: 17, 17, 17;"
                                "}";
};
#endif // ENTRYWINDOW_H
