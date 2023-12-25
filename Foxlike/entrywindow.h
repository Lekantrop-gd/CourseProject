#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H
#include <QMainWindow>
#include "user.h"
#include "registrationwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EntryWindow; }
QT_END_NAMESPACE

class EntryWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void userLoggedIn(User* user);
    void hidden();

public:
    EntryWindow(QWidget *parent = nullptr);
    ~EntryWindow();

private slots:
    void on_continueButton_clicked();

    void on_continueAsGuestButton_clicked();

    void on_continueButton_2_clicked();

private:
    Ui::EntryWindow *ui;

    RegistrationWindow *registrationWindow;

    void closeEvent(QCloseEvent* event) override;
};
#endif // ENTRYWINDOW_H
