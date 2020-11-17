#include "mainwindow.h"
#include "mainwindow_init.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow_init w;
    w.show();
    return a.exec();
}
