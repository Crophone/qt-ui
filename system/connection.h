#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
static bool createConnection()
{
        QSqlDatabase db= QSqlDatabase::addDatabase("QSQLITE","connection");
        db.setDatabaseName("system.db");
        if(!db.open())
        {
          QMessageBox::critical(0,"Can not open database","Unable to establish a database connection.",QMessageBox::Cancel);
            return false;
        }

        QSqlQuery query(db);


        //新建admin表
        query.exec(QString("create table admin(adminID varchar primary key,pwd  varchar(20))"));
        query.exec(QString("insert into admin values('xiaobing','123456')"));
        query.exec(QString("insert into admin values('xiaoshan','123456')"));
        query.exec(QString("insert into admin values('xiaoyang','123456')"));

        //新建student表，studentID设置为主键，还有一个name项。primary key 表明该字段是主键，不能为空，不能有重复的值
        //学生：学号（主键） 密码 姓名 性别
        query.exec(QString("create table student(studentID varchar primary key,pwd varvhar,name varchar,gender bool,dorm varchar,tele varchar)"));
        query.exec(QString("insert into student values('201630661234','123456','李强',1,'C10-100','15521001234')"));
        query.exec(QString("insert into student values('201630661235','123456','马路',0,'C10-101','15521001235')"));
        query.exec(QString("insert into student values('201630661236','123456','光良',1,'C10-100','15521001236')"));
         qDebug()<<"system:";

        query.exec("select * from student");
        while(query.next())
        {
            qDebug()<<query.value(0).toString()<<query.value(1).toString();
        }

        query.exec("select * from admin");
        qDebug()<<"管理员账号密码";
        while(query.next())
        {
            qDebug()<<query.value(0).toString()<<query.value(1).toString();
        }
        return true;
}




#endif // CONNECTION_HFFf
