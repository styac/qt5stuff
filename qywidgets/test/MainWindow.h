#pragma once
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

#include "ui_MainWindow.h"
#include "QyWidgetVectorSpec.h"
#include "QyButton.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

public slots:
    void changedValueMiddle(double val, int valueId);
    void changedValueBig(double val, int valueId);
    void controlClicked(int kmods, bool ct, bool sw, int val, int goupIndex);
    void controlClicked0(int kmods, bool ct, bool sw, int val, int goupIndex);

private:
    Ui::MainWindow ui;
    QWidget *pt;
    QyControllerVectorGrid * controllerVectorGrid;
    QyWidgetVectorGrid<QyIndicator>  * controllerVectorGridIndicator;
//    QyWidgetVector<QyController,QGridLayout>    controllerVectorGrid;
//    QyWidgetVector<QyController,QBoxLayout>     controllerVectorBox;

    QyButton button;

};
