#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Программа генерации и прохождения лабиринтов");
    w.show();

    return a.exec();
}
