#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, passwordInput()
, count(0)
{
    ui.setupUi(this);

//    passwordInput = new QsPasswordInput();
    passwordInput = new QsPasswordInput(ui.centralWidget);
    ui.gridLayout->addWidget(passwordInput, 1, 1, 1, 1);

    QObject::connect( passwordInput, SIGNAL(returnPressed()),
            this, SLOT(passwordEntered()));

    QObject::connect( ui.type_pw_input, SIGNAL(returnPressed()),
            this, SLOT(passwordEntered_type()));

    QObject::connect( ui.type_pw_input, SIGNAL(textChanged()),
            this, SLOT(passwordEntered_type()));

    QObject::connect( ui.retype_pw_input, SIGNAL(returnPressed()),
            this, SLOT(passwordEntered_retype()));

    QObject::connect( ui.retype_pw_input, SIGNAL(returnPressed()),
            this, SLOT(passwordEntered_retype()));

    QObject::connect( ui.type_pw_input, SIGNAL(passwordTooShort()),
            this, SLOT(passwordTooShort()));

    QObject::connect( ui.type_pw_input, SIGNAL(passwordTooLong()),
            this, SLOT(passwordTooLong()));

    passwordInput->setClipboardEnabled(true);
    ui.type_pw_input->setClipboardEnabled(true);
    ui.type_pw_input->setMaxLength(10);
    ui.retype_pw_input->setClipboardEnabled(true);
    passwordInput->setFrame(true); // TODO: doesn't work with plasma, only with fusion (opensuse 15.0)
}


void MainWindow::passwordEntered_type()
{
    std::string pw1;
    ui.type_pw_input ->text( pw1, false );
    std::cout
        << " passwordEntered_type: " << pw1
        << std::endl;
    if( ! ui.retype_pw_input->setComparePassword( * ui.type_pw_input ) ) {
        std::cout
            << " setComparePassword not set"
            << std::endl;
    }
}

void MainWindow::passwordEntered_retype()
{
    std::string pw1;
    ui.retype_pw_input ->text( pw1, false );
    std::cout
        << " passwordEntered_retype: " << pw1
        << std::endl;
}

void MainWindow::passwordEntered()
{
    ++count;
    bool del = (count & 7) == 7;
    std::string pw1;
    passwordInput->text( pw1, false );

    std::string pw2;
    passwordInput->text( pw2, false );

    std::string pw3;
    passwordInput->text( pw3, del );

    std::string pw4;
    passwordInput->text( pw4, false );

    std::cout
        << "  " << count
        << "  pw1: " << pw1
        << "  pw2: " << pw2
        << "  pw3: " << pw3
        << "  pw4: " << pw4
        << std::endl;

    for(auto i=0u; i<pw1.size(); ++i ) {
        std::cout << " " << std::hex << uint16_t(pw1[i]);
    }
    std::cout << std::endl;

    // set color
    passwordInput->setPasswordOk( count & 1 );

}

void MainWindow::passwordTooShort()
{
    std::cout
        << " passwordTooShort "
        << std::endl;
}

void MainWindow::passwordTooLong()
{
    std::cout
        << " passwordTooLong "
        << std::endl;

}
