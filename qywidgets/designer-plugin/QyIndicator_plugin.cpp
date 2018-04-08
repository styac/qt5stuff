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

#include "QyIndicator_plugin.h"
#include "QyIndicator.h"

QWidget* QyIndicator_plugin::createWidget(QWidget *parent)
{
    return new QyIndicator(parent);
}

QIcon QyIndicator_plugin::icon() const
{
    return QIcon();
}

QString QyIndicator_plugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"QyIndicator\" name=\"indicator\">\n"
//           "  <property name=\"toolTip\" >\n"
//           "   <string>indicator widget</string>\n"
//           "  </property>\n"
//           "  <property name=\"whatsThis\" >\n"
//           "   <string>indicator widget</string>\n"
//           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

bool QyIndicator_plugin::isContainer() const
{
    return false;
}

QyIndicator_plugin::QyIndicator_plugin(QObject *parent)
:  QObject(parent)
, initialized(false)
{
}

void QyIndicator_plugin::initialize(QDesignerFormEditorInterface *)
{
    initialized = true;
}

bool QyIndicator_plugin::isInitialized() const
{
    return initialized;
}

QString QyIndicator_plugin::name() const
{
    return QStringLiteral("QyIndicator");
}

QString QyIndicator_plugin::group() const
{
    return QStringLiteral("Qy Widgets");
}

QString QyIndicator_plugin::toolTip() const
{
    return QStringLiteral("indicator widget");
}

QString QyIndicator_plugin::whatsThis() const
{
    return QStringLiteral("indicator widget");
}

QString QyIndicator_plugin::includeFile() const
{
    return QStringLiteral("QyIndicator.h");
}

