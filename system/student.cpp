#include "student.h"
#include "ui_student.h"
#include "login.h"
#include <QFormLayout>
#include <QString>
#include <QLineEdit>
#include "login.h"
#include <QSqlDriver>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlDatabase>
#include <QTime>
Student::Student(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Student)
{
    ui->setupUi(this);
    QString centralwidget_style="QWidget #centralwidget{"
                                "border-image: url(:/assets/assets/student.jpg);"
                                "}";

    ui->centralwidget->setStyleSheet(centralwidget_style);


    QString button_style="QPushButton{"
                         "background-color:black;"
                         "color: white; "
                         "border-radius: 10px; "
                         "border: 2px groove gray;"
                         "border-style: outset;"
                         "}"

                         "QPushButton:hover{"
                         "background-color:white; "
                         "color: black;"
                         "}"

                         "QPushButton:pressed{"
                         "background-color:rgb(85, 170, 255);"
                         " border-style: inset;"
                         " }"
            ;

    ui->backPushButton->setStyleSheet(button_style);
    ui->submitPushButton->setStyleSheet(button_style);
    ui->pushButton->setStyleSheet(button_style);
    ui->pushButton_2->setStyleSheet(button_style);
    ui->backPushButton->setStyleSheet(button_style);
    ui->pwdModifyButton->setStyleSheet(button_style);
    ui->pushButton_3->setStyleSheet(button_style);
    ui->pushButton_2->setText("展示信息");
    ui->pushButton_2->setEnabled(false);
    ui->frame->move(180,70);
    ui->frame->repaint();
    ui->frame_2->move(859,90);
}

Student::~Student()
{
    delete ui;
}

void Student::sleep(int ms)
{

    QTime reachTime = QTime::currentTime().addMSecs(ms);
    while( QTime::currentTime()<reachTime )
    {
        //       qDebug()<"使用while语句循环";
    }
    return;

}

void Student::receiveValue(QString ID)
{

    QSqlDatabase db =QSqlDatabase::database("connection");
    if(!db.open())
    {
        QMessageBox::critical(0,"Can not open database","Unable to establish a database connection.",QMessageBox::Cancel);

    }
    QSqlQuery student(db);

    //得到总人数
    student.exec("select * from student");
    int numRows;
    if(db.driver()->hasFeature(QSqlDriver::QuerySize))
    {
        qDebug()<<"has feature:query size";
        numRows=student.size();
    }
    else
    {
        qDebug()<<"no feature:query size";
        student.last();
        numRows=student.at()+1;
    }
    QString n=QString::number(numRows,10);




    QString value="select * from student where studentID ='"+ID+"'";
    student.exec(value);
    student.next();
    QSqlRecord record=student.record();
    QString name=record.value("name").toString();
    QString gender=record.value("gender").toBool()?"男":"女";
    QString dorm=record.value("dorm").toString();
    QString tele=record.value("tele").toString();


    ui->name->setText("姓名:\n"+name);
    ui->ID->setText("学号:\n"+ID);
    ui->gender->setText("性别:\n"+gender);
    ui->dorm->setText("宿舍:\n"+dorm);
    ui->total->setText("班级总人数:\n"+n);
    ui->TelelineEdit->setText(tele);

}

void Student::on_submitPushButton_clicked()
{
    //事务
    QSqlDatabase::database().transaction();
    QSqlDatabase db =QSqlDatabase::database("connection");
    if(!db.open())
    {
        QMessageBox::critical(0,"Can not open database","Unable to establish a database connection.",QMessageBox::Cancel);

    }
    QSqlQuery student(db);
    QString newTele = ui->TelelineEdit->text();
    QString ID = ui->ID->text();
    newTele.remove("电话:");
    qDebug()<<newTele;
    QString exe = "update student set tele = '"+newTele+"'"+" where studentID = "+ID;
    qDebug()<<exe;
    student.exec(exe);
    QSqlDatabase::database().commit();
    QMessageBox::about(0,"提示","修改电话号码成功");

    student.exec("select * from student");
    while(student.next())
    {
        qDebug()<<student.value(0).toString();
    }
}

void Student::on_backPushButton_clicked()
{
    Login *login=new Login;
    login->show();
    this->close();
}

void Student::on_pushButton_clicked()
{   qDebug()<<"修改密码";
    int initWidth=ui->frame->width()+ui->frame->x();
    int initWidth_2=ui->frame_2->x()-180;
    qDebug()<<"开始展示时的initWidth:"<<initWidth;
    for(int i=1;i<=50;i++)
    {
        qDebug()<<"进入for循环";
        int x=ui->frame->x();
        int y=ui->frame->y();
        ui->frame->move(x-(initWidth)/50,y);
        ui->frame->repaint();
        qDebug()<<"x:"<<x;
        qDebug()<<"Y:"<<y;
        int x_2=ui->frame_2->x();
        int y_2=ui->frame_2->y();
        ui->frame_2->move(x_2-initWidth_2/50,y_2);
        ui->frame_2->repaint();
        sleep(20);
    }

    qDebug()<<"循环结束";
    ui->pushButton->setText("修改密码");
    ui->pushButton_2->setText("←展示信息");
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
}



void Student::on_pushButton_2_clicked()
{
    int initWidth=-ui->frame->x()+180;
    int initWidth_2=ui->centralwidget->width()-ui->frame_2->x();

    qDebug()<<"开始展示时的initWidth:"<<initWidth;

    for(int i=1;i<50;i++)
    {
        qDebug()<<"进入for循环";
        int x=ui->frame->x();
        int y=ui->frame->y();
        int x_2=ui->frame_2->x();
        int y_2=ui->frame_2->y();
        ui->frame->move(x+(initWidth)/50,y);
        ui->frame->repaint();
        qDebug()<<"x:"<<x;
        qDebug()<<"Y:"<<y;
        ui->frame_2->move(x_2+initWidth_2/50,y_2);
        ui->frame_2->repaint();
        sleep(20);
    }
    ui->frame->move(180,70);
    ui->pushButton->setEnabled(true);
    ui->pushButton->setText("→修改密码");
    ui->pushButton_2->setText("展示信息");
    ui->pushButton_2->setEnabled(false);
}



void Student::on_pwdModifyButton_clicked()
{

    QSqlDatabase db =QSqlDatabase::database("connection");
    if(!db.open())
    {
        QMessageBox::critical(0,"Can not open database","Unable to establish a database connection.",QMessageBox::Cancel);

    }
    QSqlQuery student(db);

    QString ID=ui->ID->text();
    ID.remove("学号:\n");
    QString value="select * from student where studentID ='"+ID+"'";
    qDebug()<<value;
    student.exec(value);
    student.next();
    qDebug()<<student.value(0).toString()<<student.value(0).toString();
    QString pwdOld=ui->pwdOld->text();
    QString pwdNew=ui->pwdNew->text();
    QString pwdNew2=ui->pwdNew_2->text();


    if(pwdOld!=student.value(1).toString())
    {
        QMessageBox::warning(0,"错误","密码错误,请重新输入",QMessageBox::Cancel);
        ui->pwdOld->clear();
        ui->pwdNew->clear();
        ui->pwdNew_2->clear();
    }
    else{
        if(pwdNew==NULL&&pwdNew.length()<6)
        {
            QMessageBox::warning(0,"警告","新密码长度不能小于6,请重新输入",QMessageBox::Cancel);
            ui->pwdNew->clear();
            ui->pwdNew_2->clear();
            ui->pwdNew->setFocus();
        }

        else  if(pwdNew!=pwdNew2)
        {     QMessageBox::warning(0,"错误","新密码不一致，请重新输入",QMessageBox::Cancel);
            ui->pwdNew->clear();
            ui->pwdNew_2->clear();
        }
        else
        {
            QString exe = "update student set pwd = '"+pwdNew+"'"+" where studentID = "+ID;
            qDebug()<<exe;
            student.exec(exe);
            QSqlDatabase::database().commit();
            QMessageBox::about(0,"提示","修改密码成功");
            ui->pwdOld->clear();
            ui->pwdNew->clear();
            ui->pwdNew_2->clear();
        }
    }
}


void Student::on_pushButton_3_clicked()
{

    QSqlDatabase db =QSqlDatabase::database("connection");
    if(!db.open())
    {
        QMessageBox::critical(0,"Can not open database","Unable to establish a database connection.",QMessageBox::Cancel);

    }
    QSqlQuery student(db);

    QString ID=ui->ID->text();
    ID.remove("学号:\n");
    QString value="select * from student where studentID ='"+ID+"'";
    qDebug()<<value;
    student.exec(value);
    student.next();
    QString exe = "update student set pwd = '123456'  where studentID = "+ID;

    qDebug()<<exe;
    student.exec(exe);
    QSqlDatabase::database().commit();
    QMessageBox::about(0,"提示","成功修改为默认密码");

}
