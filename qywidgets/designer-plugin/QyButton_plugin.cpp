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

#include "QyButton_plugin.h"
#include "QyButton.h"

QWidget* QyButton_plugin::createWidget(QWidget *parent)
{
    return new QyButton(parent);
}

QIcon QyButton_plugin::icon() const
{
    return QIcon();
}

QString QyButton_plugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"QyButton\" name=\"button\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>20</width>\n"
           "    <height>20</height>\n"
           "   </rect>\n"
           "  </property>\n"

//           "  <property name=\"toolTip\" >\n"
//           "   <string>controller widget</string>\n"
//           "  </property>\n"
//           "  <property name=\"whatsThis\" >\n"
//           "   <string>controller widget</string>\n"
//           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

bool QyButton_plugin::isContainer() const
{
    return false;
}

QyButton_plugin::QyButton_plugin(QObject *parent)
: QObject(parent)
, initialized(false)

{
}

void QyButton_plugin::initialize(QDesignerFormEditorInterface *)
{
    initialized = true;
}

bool QyButton_plugin::isInitialized() const
{
    return initialized;
}

QString QyButton_plugin::name() const
{
    return QStringLiteral("QyButton");
}

QString QyButton_plugin::group() const
{
    return QStringLiteral("Qy Widgets");
}

QString QyButton_plugin::toolTip() const
{
    return QStringLiteral("button widget");
}

QString QyButton_plugin::whatsThis() const
{
    return QStringLiteral("generic button widget");
}

QString QyButton_plugin::includeFile() const
{
    return QStringLiteral("QyButton.h");
}

