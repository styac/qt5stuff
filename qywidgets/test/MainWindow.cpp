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
, button(parent)
//, controllerVectorBox(4,QBoxLayout::LeftToRight,pt)
{
    ui.setupUi(this);


    QObject::connect( ui.dial_test_middle, &QyAbstractController::valueChanged,
        this, &MainWindow::changedValueMiddle );

    ui.dial_test_middle_sym->setId(1);
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
    QObject::connect( ui.dial_test_big, &QyController::controlClicked,
        this, &MainWindow::controlClicked );


    StringVectorType colLabels;
    StringVectorType rowLabels;

    colLabels.push_back("col0");
    colLabels.push_back("col111");
    colLabels.push_back("col222222");

    rowLabels.push_back("row0");
    rowLabels.push_back("row1111");

    controllerVectorGrid = new QyWidgetVectorGrid<QyController>(2,3,false,"objname",&rowLabels, &colLabels);
    pt = new QWidget(ui.centralWidget);
    pt->setLayout( controllerVectorGrid->layout() );

    QSize wsize(80,100);
    QSize vecsize = controllerVectorGrid->applySize(wsize);
    controllerVectorGrid->applyId(0,0);
    pt->setGeometry(530,290,vecsize.width(),vecsize.height());

    auto&  tpgrid = controllerVectorGrid->widgets();
    QObject::connect( tpgrid[0], &QyController::controlClicked,
        this, &MainWindow::controlClicked0 );

    QObject::connect( tpgrid[1], &QyController::controlClicked,
        this, &MainWindow::controlClicked );
    QObject::connect( tpgrid[2], &QyController::controlClicked,
        this, &MainWindow::controlClicked );
    QObject::connect( tpgrid[3], &QyController::controlClicked,
        this, &MainWindow::controlClicked );
    QObject::connect( tpgrid[4], &QyController::controlClicked,
        this, &MainWindow::controlClicked );
    QObject::connect( tpgrid[5], &QyController::controlClicked,
        this, &MainWindow::controlClicked );

    tpgrid[0]->setEmitSliderValue(true);
    QObject::connect( tpgrid[0], &QyController::sliderPositionChanged,
        tpgrid[3], &QyController::setSliderPosition );

//    auto const&  tpgbox = controllerVectorBox.widgets();

//    QyControllerVectorGrid * controllerVectorGrid1 = new QyControllerVectorGrid(2,3,false,"objname",&rowLabels, &colLabels);
//    QyControllerVectorGrid * controllerVectorGrid2 = new QyControllerVectorGrid(2,3,false,"objname",&rowLabels, &colLabels);


}

void MainWindow::controlClicked(int kmods, bool ct, bool sw, int id, int goupIndex )
{
    qDebug() << "++x++++ id " << id
        << " goupIndex " << goupIndex
        << " ct " << ct
        << " sw " << sw
        <<  " kmods " << kmods;
}

void MainWindow::controlClicked0(int kmods, bool ct, bool sw, int id, int goupIndex )
{
    qDebug() << "++0++++ id " << id
        << " goupIndex " << goupIndex
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
