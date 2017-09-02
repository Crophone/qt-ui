#include "mainwindow.h"
#include <QApplication>
#include "connection.h"
#include <QObject>
#include <QDebug>
#include <QTextCodec>
#include "login.h"
#include "student.h"
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
//连接数据库
    if(!createConnection())
        return 1;

    Login login ;
    login.show();

    return a.exec();
}
