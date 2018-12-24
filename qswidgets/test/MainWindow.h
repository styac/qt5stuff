#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "QsPasswordInput.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

public Q_SLOTS:
    void passwordEntered();

private:
    Ui::MainWindow  ui;
    QsPasswordInput *passwordInput;
    int count;
};

#endif // MAINWINDOW_H
