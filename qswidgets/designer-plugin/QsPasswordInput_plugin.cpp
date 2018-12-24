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

#include "QsPasswordInput_plugin.h"
#include "QsPasswordInput.h"

QWidget* QsPasswordInput_plugin::createWidget(QWidget *parent)
{
    return new QsPasswordInput(parent);
}

QIcon QsPasswordInput_plugin::icon() const
{
    return QIcon();
}

QString QsPasswordInput_plugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"QsPasswordInput\" name=\"input\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>113</width>\n"
           "    <height>26</height>\n"
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

bool QsPasswordInput_plugin::isContainer() const
{
    return false;
}

QsPasswordInput_plugin::QsPasswordInput_plugin(QObject *parent)
: QObject(parent)
, initialized(false)

{
}

void QsPasswordInput_plugin::initialize(QDesignerFormEditorInterface *)
{
    initialized = true;
}

bool QsPasswordInput_plugin::isInitialized() const
{
    return initialized;
}

QString QsPasswordInput_plugin::name() const
{
    return QStringLiteral("QsPasswordInput");
}

QString QsPasswordInput_plugin::group() const
{
    return QStringLiteral("Qs Widgets");
}

QString QsPasswordInput_plugin::toolTip() const
{
    return QStringLiteral("password input widget");
}

QString QsPasswordInput_plugin::whatsThis() const
{
    return QStringLiteral("generic password input widget");
}

QString QsPasswordInput_plugin::includeFile() const
{
    return QStringLiteral("QsPasswordInput.h");
}

