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


MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, pt()
, controllerVectorGrid()
, controllerVectorGridIndicator()
//, controllerVectorBox(4,QBoxLayout::LeftToRight,pt)
{
    ui.setupUi(this);
    QObject::connect( ui.dial_test_middle, &QyAbstractController::valueChanged,
        this, &MainWindow::changedValueMiddle );

    ui.dial_test_middle_sym->setValueId(1);
    QObject::connect( ui.dial_test_middle_sym, &QyAbstractController::valueChanged,
        this, &MainWindow::changedValueMiddle );

    // direct connection
    QObject::connect( ui.dial_test_big, &QyAbstractController::sliderPositionChanged,
        ui.dial_test_middle, &QyAbstractController::setSliderPosition );


    ui.dial_test_middle->setSuffix("[mV]");
    ui.dial_test_middle->setRemoteControlled(true);

    ui.dial_test_big->setCaption("caption");
    ui.dial_test_big->setEmitSliderValue(true);
    ui.dial_test_middle->setSuffix("[dB]");

    ui.dial_test_middle_sym->setSymmetric(true);
    ui.dial_test_middle_sym->setRange(-1000.0, 1000.0);
    ui.dial_test_middle_sym->setSuffix("[%]");

    ui.controller_mid_1->setSuffix("A [Hz]");
    ui.controller_mid_2->setSuffix("B [Hz]");
    ui.controller_mid_3->setSuffix("C [Hz]");
    ui.controller_mid_4->setSuffix("D [Hz]");
    ui.controller_mid_5->setSuffix("E [Hz]");

    ui.dial_test_big->registerTransformFunctions(
        QyBase::TransformExp2::slider2value,
        QyBase::TransformExp2::value2slider,
        QyBase::TransformExp2::setValueRange );

    ui.dial_test_big->setRange(20.0,20000.0);
    ui.controller_mid_4->setDisabled(true);
    QObject::connect( ui.dial_test_big, &QyController::userEvent,
        this, &MainWindow::handleUserEvent );

    pt = new QWidget(ui.centralWidget);

    StringVectorType colLabels;
    StringVectorType rowLabels;

    colLabels.push_back("col0");
    colLabels.push_back("col1");
    colLabels.push_back("col2");

    rowLabels.push_back("row0");
    rowLabels.push_back("row1");

// not implemented yet
//    controllerVectorGridIndicator = new QyWidgetVectorGrid<QyIndicator>(2,3,pt,&colLabels,&rowLabels);

    controllerVectorGrid = new QyWidgetVectorGrid<QyController>(2,3,false,"objname",&colLabels,&rowLabels,pt);
    QSize wsize(80,100);
    QSize vecsize = controllerVectorGrid->applySize(wsize);
    controllerVectorGrid->applyId(0,0);
    pt->setGeometry(530,290,vecsize.width(),vecsize.height());
    auto&  tpgrid = controllerVectorGrid->widgets();
//    auto const&  tpgbox = controllerVectorBox.widgets();


    QObject::connect( tpgrid[0], &QyController::userEvent,
        this, &MainWindow::handleUserEvent0 );

    tpgrid[0]->setEmitSliderValue(true);
    QObject::connect( tpgrid[0], &QyController::sliderPositionChanged,
        tpgrid[3], &QyController::setSliderPosition );
}

void MainWindow::handleUserEvent(int kmods, bool ct, bool sw, int val)
{
    qDebug() << "++++++ handleUserEvent " << val
        << " ct " << ct
        << " sw " << sw
        <<  " kmods " << kmods;
}

void MainWindow::handleUserEvent0(int kmods, bool ct, bool sw, int val)
{
    qDebug() << "++++++ handleUserEvent0 " << val
        << " ct " << ct
        << " sw " << sw
        <<  " kmods " << kmods;
    controllerVectorGrid->widgets()[3]->setRemoteControlled(ct);
    controllerVectorGrid->widgets()[3]->setInvertSetSliderPos(sw);
}

void MainWindow::changedValueMiddle(double val, int valueId)
{
    qDebug() << "++++++ changedValueMiddle " << val << " valueId " << valueId;
}


void MainWindow::changedValueBig(double val, int valueId)
{
    qDebug() << "++++++ changedValueBig " << val << " valueId " << valueId;
    ui.dial_test_middle->setValue(val);
}
