#ifndef STUDENT_H
#define STUDENT_H

#include <QMainWindow>

namespace Ui {
class Student;
}

class Student : public QMainWindow
{
    Q_OBJECT

public:
    explicit Student(QWidget *parent = 0);
    ~Student();
    void sleep(int );

private slots:
    void receiveValue(QString);

    void on_submitPushButton_clicked();

    void on_backPushButton_clicked();

    void on_pushButton_clicked(); //进入修改密码页面

    void on_pushButton_2_clicked();//进入展示信息页面

    void on_pushButton_3_clicked();//修改为默认密码

    void on_pwdModifyButton_clicked();//修改为新密码

private:
    Ui::Student *ui;
};

#endif // STUDENT_H
