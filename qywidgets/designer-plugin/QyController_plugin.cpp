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

#include "QyController_plugin.h"
#include "QyController.h"

QWidget* QyController_plugin::createWidget(QWidget *parent)
{
    return new QyController(parent);
}

QIcon QyController_plugin::icon() const
{
    return QIcon();
}

QString QyController_plugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"QyController\" name=\"controller\">\n"
//           "  <property name=\"toolTip\" >\n"
//           "   <string>controller widget</string>\n"
//           "  </property>\n"
//           "  <property name=\"whatsThis\" >\n"
//           "   <string>controller widget</string>\n"
//           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

bool QyController_plugin::isContainer() const
{
    return false;
}

QyController_plugin::QyController_plugin(QObject *parent)
: QObject(parent)
, initialized(false)

{
}

void QyController_plugin::initialize(QDesignerFormEditorInterface *)
{
    initialized = true;
}

bool QyController_plugin::isInitialized() const
{
    return initialized;
}

QString QyController_plugin::name() const
{
    return QStringLiteral("QyController");
}

QString QyController_plugin::group() const
{
    return QStringLiteral("Qy Widgets");
}

QString QyController_plugin::toolTip() const
{
    return QStringLiteral("controller widget");
}

QString QyController_plugin::whatsThis() const
{
    return QStringLiteral("generic controller widget");
}

QString QyController_plugin::includeFile() const
{
    return QStringLiteral("QyController.h");
}

