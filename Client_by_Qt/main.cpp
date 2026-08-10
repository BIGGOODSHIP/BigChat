#include "mainwindow.h"
#include"config.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(icon_path));
    MainWindow w;
    w.show();
    return QApplication::exec();
}
