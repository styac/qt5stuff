#include "MainWindow.h"
#include <QApplication>
#include <QDebug>
#include <string>
#include <iostream>

#include "utils.h"

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

