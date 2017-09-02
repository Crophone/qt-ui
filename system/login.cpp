#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QSysInfo>
#include <QTimer>
#include <QDateTime>
#include "student.h"
#include "mainwindow.h"
#include "connection.h"
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    QString button_style="QPushButton{"
                         "background-color:rgb(137,185,226);"
                         "color: white; "
                         "border-radius: 10px; "
                         "border: 2px groove gray;"
                         "border-style: outset;"
                         "}"

                         "QPushButton:hover{"
                         "background-color:blue; "
                         "color: black;"
                         "}"

                         "QPushButton:pressed{"
                         "background-color:red;"
                         " border-style: inset;"
                         " }"
            ;
    QString label_style="QLabel{"
                        "color: white; "
                        "border-radius:10px;"
                        "border: 2px dashed gray;"

                        "}";

    QString radioButton_style="QRadioButton{"
                              " color: white; "
                              "border-radius:10px;"
                              "border: 2px groove gray;"
                              "}";
    QString lineEdit_style="QLineEdit{"
                              " color: white; "
                              "border-radius:10px;"
                              "border: 2px groove gray;"
                              "background-color:white;"
                              "}";


    ui->loginPushButton->setStyleSheet(button_style);
    ui->cancelPushButton->setStyleSheet(button_style);
    ui->DateLabel->setStyleSheet(label_style);
    ui->timeLabel->setStyleSheet(label_style);
    ui->hello->setStyleSheet(label_style);
    ui->label_2->setStyleSheet(label_style);
    ui->label_5->setStyleSheet(label_style);

    ui->adminRadioButton->setStyleSheet(radioButton_style);
    ui->studentRadioButton->setStyleSheet(radioButton_style);

    ui->IDIineEdit->setStyleSheet(lineEdit_style);
    ui->pwdLineEdit->setStyleSheet(lineEdit_style);

#ifdef  Q_OS_WIN
    qDebug()<<"Hello Qt World on Windows";

    if(QSysInfo::WindowsVersion== QSysInfo::WV_XP){
        ui->hello ->setText(tr("Windows XP!微软玩家您好!"));
    }
    else if(QSysInfo::WindowsVersion==QSysInfo::WV_10_0){
        ui->hello->setText(tr(" Windows 10 微软玩家您好!"));
    }
#elif defined(Q_OS_UNIX)
    {
        ui->hello->setText(tr("UNIX玩家您好"));
    }
#else
    { ui->hello->setText(tr("神秘玩家您好"));
    }
#endif
    timeID = startTimer(1000);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(qtimeSlot()));
    timer->start(1000);

//日期
    QDate qdateObj = QDate::currentDate();
    QString strDate = qdateObj.toString("yyyy 年 MMM  d日  dddd"); //年、月、日、星期、
    strDate.prepend(" ");
    ui->DateLabel->setText (strDate);
//时间
    QTime qtimeObj = QTime::currentTime();
    int hour =qtimeObj.hour();
    int minute = qtimeObj.minute();
    int second = qtimeObj.second();
    QString strTime = qtimeObj.toString(" ap ");
    QString h = hour<10?"0"+QString::number(hour,10):QString::number(hour,10);
    QString min = minute<10?"0"+QString::number(minute,10):QString::number(minute,10);
    QString sec=second<10? "0"+QString::number(second,10):QString::number(second,10);
    h.prepend(strTime);
    h.prepend("程序启动时间: ");
    h.append(":"+min);
    h.append(":"+sec);
    //   ui->openTime->setText(h);
    ui->studentRadioButton->setChecked(true);

    h.remove ("程序启动时间: ");
    h.prepend("   ");
    ui->timeLabel->setText(h);

}

Login::~Login()
{
    delete ui;
    ui->studentRadioButton->setChecked(true);
}

void Login::timerEvent(QTimerEvent * event)
{
    if(event->timerId()==timeID)
    {
        QTime qtimeObj = QTime::currentTime();

        int hour =qtimeObj.hour();
        int minute = qtimeObj.minute();
        int second = qtimeObj.second();
        QString strTime = qtimeObj.toString(" ap ");
        QString h = hour<10?"0"+QString::number(hour,10):QString::number(hour,10);
        QString min = minute<10?"0"+QString::number(minute,10):QString::number(minute,10);
        QString sec=second<10? "0"+QString::number(second,10):QString::number(second,10);

        h.prepend(strTime);
        h.prepend("  ");
        h.append(":"+min);
        h.append(":"+sec);

        ui->timeLabel->setText(h);

    }
}

void Login::on_loginPushButton_clicked()
{

    QSqlDatabase db =QSqlDatabase::database("connection");
    if(!db.open())
    {
        QMessageBox::critical(0,"Can not open database","Unable to establish a database connection.",QMessageBox::Cancel);
        return;
    }
    QSqlQuery system(db);
    //连接至数据库



    qDebug()<<"connection to db database :";
    system.exec("select * from student");
    qDebug()<<"学生账号密码";
    while(system.next())
    {
        qDebug()<<system.value(0).toString()<<system.value(1).toString();
    }

    system.exec("select * from admin");
    qDebug()<<"管理员账号密码";
    while(system.next())
    {
        qDebug()<<system.value(0).toString()<<system.value(1).toString();
    }
    //显示对应账号密码






    QString ID = ui->IDIineEdit->text();
    QString pwd= ui->pwdLineEdit->text();
    if(!ui->studentRadioButton->isChecked()&&!ui->adminRadioButton->isChecked())
    {
        QMessageBox::warning(0, "错误", "请选择学生入口或者管理员入口", QMessageBox::Yes);
    }
    else   if(ui->studentRadioButton->isChecked()){

                qDebug()<<"学生入口";
                QString str="select * from student where studentID='"+ID+"'";
                qDebug()<<str;
                system.exec(str);
                system.next();

                qDebug()<<system.value(0).toString()<<system.value(1).toString();

                if(ID==NULL||pwd==NULL)
                {
                    QMessageBox::warning(0, "错误", "学生账号或密码不能为空，请重新输入", QMessageBox::Yes);

                }
                else if(system.value(1).toString()!=pwd)
                {
                    QMessageBox::warning(0, "错误", "账号或密码错误，请重新输入", QMessageBox::Yes);
                     ui->pwdLineEdit->clear();
                     ui->pwdLineEdit->setFocus();
                }
                else if(system.value(1).toString()==pwd)
                {
                    qDebug()<<ID<<"学生登陆成功";
                    Student *studentPtr= new Student;
                    connect(this,SIGNAL(showStudent(QString)),studentPtr,SLOT(receiveValue(QString)));
                    emit showStudent(QString(ID));
                    studentPtr->show();
                     this->close();
                }
//        Student *studentPtr= new Student;
//        studentPtr->show();
//        this->close();
    }



    //管理者admin入口
    else if (ui->adminRadioButton->isChecked())
    {
                qDebug()<<"管理员入口";

                QString str="select * from admin where adminID ='"+ID+"'";
                qDebug()<<str;
                system.exec(str);
                system.next();
                qDebug()<<system.value(0).toString()<<system.value(1).toString();

                if(ID==NULL||pwd==NULL)
                {
                    QMessageBox::warning(0, "错误", "管理员账号或密码不能为空，请重新输入", QMessageBox::Cancel);

                }

                else
                    if(system.value(1).toString()!=pwd)
                    {
                        QMessageBox::warning(0,"错误","账号或密码错误，请重新输入", QMessageBox::Cancel);
                        ui->pwdLineEdit->clear();
                        ui->pwdLineEdit->setFocus();
                    }

                    else if (system.value(1).toString()==pwd)
                    {

                        MainWindow *adminPtr = new MainWindow;

                        connect(this,SIGNAL(showAdmin(QString)),adminPtr,SLOT(receiveValue(QString)));
                        emit showAdmin(QString (ID));
                        adminPtr->show();
                        this->close();
                    }

//        MainWindow *adminPtr = new MainWindow;
//        adminPtr->show();
//        this->close();
    }
}

void Login::on_cancelPushButton_clicked()
{
    ui->IDIineEdit->clear();
    ui->pwdLineEdit->clear();
    ui->IDIineEdit->setFocus();
}
