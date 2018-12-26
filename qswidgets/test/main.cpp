#include "MainWindow.h"
#include <QApplication>
#include <QDebug>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    MainWindow w;

//    QString style(
//        " QsPasswordInput:focus {"
//        " border-style: outset;"
//        " border-width: 1px;"
//        " outline-color: black; }"
//    );
//    a.setStyleSheet( style );

    w.show();
    return a.exec();
}

