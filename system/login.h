#ifndef LOGIN_H
#define LOGIN_H
#include "connection.h"
#include <QDialog>


namespace Ui {
class Login;
}


class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
protected:
    void timerEvent(QTimerEvent*);

signals:
    void showStudent(QString ID);
    void showAdmin(QString ID);
private slots:
    void on_loginPushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::Login *ui;
    int timeID;
};

#endif // LOGIN_H
