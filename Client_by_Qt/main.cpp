#include "mainwindow.h"
#include"config.h"
#include <QApplication>
#include<QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //设置窗口图标
    a.setWindowIcon(QIcon(icon_path));
    MainWindow w;

    //加载qss
    QFile qss(":/style/stylesheet.qss");
    if(qss.open(QFile::ReadOnly)){
        qDebug("open successful!");
        QString style=QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    else{
        qDebug("open failed!");
    }
    w.show();
    return QApplication::exec();
}
