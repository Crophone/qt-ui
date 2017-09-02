#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "login.h"
#include <qsqldatabase.h>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    QString button_style2="QPushButton{"
                         "background-color:black;"
                         "color: white; "
                         "border-radius: 20px; "
                         "border: 4px groove gray;"
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
    ui->pushButton->setStyleSheet(button_style);
    ui->pushButton_2->setStyleSheet(button_style);
    ui->pushButton_3->setStyleSheet(button_style);
    ui->pushButton_4->setStyleSheet(button_style);
    ui->pushButton_5->setStyleSheet(button_style);
    ui->pushButton_6->setStyleSheet(button_style);
    ui->pushButton_7->setStyleSheet(button_style);
    ui->pushButton_8->setStyleSheet(button_style);
    ui->back->setStyleSheet(button_style2);


//    QSqlDatabase db =QSqlDatabase::database("connection");
//    if(!db.open())
//    {
//        QMessageBox::critical(0,"Can not open database","Unable to establish a database connection.",QMessageBox::Cancel);

//    }

//    qDebug()<<"  ";
//    qDebug()<<"管理者界面:";
//    QSqlQuery query(db);
//    query.exec("select * from student");
//    while(query.next())
//    {
//        qDebug()<<query.value(0).toString()<<"成功连接数据库";
//    }

 qDebug()<<"管理者界面:";
  QSqlDatabase db =QSqlDatabase::database("connection");
    model = new QSqlTableModel(this,db);
    model -> setTable("student");
    model ->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model ->select();


//设置编辑策略

    ui->tableView->setModel(model);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiveValue(QString ID)
{
    ui->admin->setText(ID);

}

//提交修改按钮
void MainWindow::on_pushButton_clicked()
{
    model->database().transaction();
    if(model->submitAll()){
        int ok=QMessageBox::warning(this,tr("提交！"),
               tr( "确定向数据库更改内容？"),QMessageBox::Yes,QMessageBox::No);
       if(ok==QMessageBox::Yes)
       {
           model->database().commit();
           QMessageBox::information(this,tr("成功"),
               tr("数据库内容更新成功"),QMessageBox::Yes);
        }


    }

    else{
        model->database().rollback();
        QMessageBox::warning(this,"tableModel",
                             tr("数据库错误：1%").arg(model->lastError().text()));

    }
}
//撤销修改
void MainWindow::on_pushButton_2_clicked()
{
    model->revertAll();
}

//根据姓名查询
void MainWindow::on_pushButton_5_clicked()
{
    QString name = ui ->lineEdit->text();
    model->setFilter(QString("name='%1'").arg(name));
    model->select();
}


//显示全表按钮
void MainWindow::on_pushButton_7_clicked()
{
    model->setTable("student");
    model->select();
}
//返回按钮
void MainWindow::on_back_clicked()
{
   Login * login = new Login;
   login->show();
   this->close();
}


void MainWindow::on_pushButton_6_clicked()
{
 model->setSort(0,Qt::AscendingOrder);
 model->select();
}

void MainWindow::on_pushButton_8_clicked()
{
    model->setSort(0,Qt::DescendingOrder);
    model->select();

}

void MainWindow::on_pushButton_4_clicked()
{
    int  curRow = ui->tableView->currentIndex().row();
    model ->removeRow(curRow);
    int ok=QMessageBox::warning(this,tr("删除当前行！"),
           tr( "删除操作不可逆，确定修改？"),QMessageBox::Yes,QMessageBox::No);

    if(ok==QMessageBox::No)
    {
        model->revertAll();
    }
    else
    {
        model->submitAll();
    }
}

//添加记录按钮
void MainWindow::on_pushButton_3_clicked()
{
    int rowNum = model->rowCount();
    int id=10;
    model->insertRow(rowNum);
    model->setData(model->index(rowNum,0),id);
    model->submitAll();

}

