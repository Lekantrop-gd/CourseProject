#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QDialog>

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QWidget
{
    Q_OBJECT

signals:
    void hidden();

public:
    explicit RegistrationWindow(QWidget *parent = nullptr);
    ~RegistrationWindow();

private slots:
    void on_continueButton_clicked();

    void on_photoButton_clicked();

private:
    Ui::RegistrationWindow *ui;

    QString profilePhoto;

    void closeEvent(QCloseEvent *event) override;
};

#endif // REGISTRATIONWINDOW_H
