/*
 * Copyright (C) 2018 Istvan Simon -- stevens37 at gmail dot com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
    QObject::connect( ui.dial_test_middle, &QyAbstractController::valueChanged,
        this, &MainWindow::changedValueMiddle );

    // direct connection
    QObject::connect( ui.dial_test_big, &QyAbstractController::sliderPositionChanged,
        ui.dial_test_middle, &QyAbstractController::setSliderPosition );


    ui.dial_test_middle->setDisabled(true);
//    ui.dial_test_middle->setEnabled(false);
    ui.dial_test_big->setEmitSliderValue(true);

    ui.dial_test_middle_sym->setSymmetric(true);
    ui.dial_test_middle_sym->setRange(-1000.0, 1000.0);


    ui.dial_test_big->registerTransformFunctions(
        QyBase::TransformExp2::slider2value,
        QyBase::TransformExp2::value2slider,
        QyBase::TransformExp2::setValueRange );

    ui.dial_test_big->setRange(20.0,20000.0);

    QObject::connect( ui.dial_test_big, &QyController::userEvent,
        this, &MainWindow::handleUserEvent );
}

void MainWindow::handleUserEvent(int val,int kmods)
{
    qDebug() << "++++++ handleUserEvent " << val << " kmods " << kmods;
}


void MainWindow::changedValueMiddle(double val)
{
    qDebug() << "++++++ changedValueMiddle " << val;
}


void MainWindow::changedValueBig(double val)
{
    qDebug() << "++++++ changedValueBig " << val;
    ui.dial_test_middle->setValue(val);
}
