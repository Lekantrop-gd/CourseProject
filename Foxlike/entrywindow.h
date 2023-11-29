#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H

#include <QMainWindow>
#include <QString>
#include "Enums.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EntryWindow; }
QT_END_NAMESPACE

class EntryWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void userLoggedIn(QString name, QString balance, AccountType accountType);

public:
    EntryWindow(QWidget *parent = nullptr);
    ~EntryWindow();

private slots:
    void on_continueButton_clicked();

    void on_continueAsGuestButton_clicked();

private:
    Ui::EntryWindow *ui;
};
#endif // ENTRYWINDOW_H
