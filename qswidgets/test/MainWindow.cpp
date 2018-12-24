#include "MainWindow.h"
#include <iostream>
#include "utils.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, passwordInput()
, count(0)
{
    ui.setupUi(this);

//    passwordInput = new QsPasswordInput();
    passwordInput = new QsPasswordInput(ui.centralWidget);
    ui.gridLayout->addWidget(passwordInput, 1, 1, 1, 1);

    QObject::connect(passwordInput, SIGNAL(returnPressed()),
            this, SLOT(passwordEntered()));
    passwordInput->setClipboardEnabled(true);
    passwordInput->setFrame(true); // TODO: doesn't work
}

void MainWindow::passwordEntered()
{
    ++count;
    std::string pw1;
    passwordInput->text( pw1, false );

    std::string pw2;
    passwordInput->text( pw2, false );

    std::string pw3;
    passwordInput->text( pw3, true );

    std::string pw4;
    passwordInput->text( pw4, false );

    std::cout
        << "  " << count
        << "  pw1: " << pw1
        << "  pw2: " << pw2
        << "  pw3: " << pw3
        << "  pw4: " << pw4
        << std::endl;

    for(auto i=0; i<pw1.size(); ++i ) {
        std::cout << " " << std::hex << uint16_t(pw1[i]);
    }
    std::cout << std::endl;
}

