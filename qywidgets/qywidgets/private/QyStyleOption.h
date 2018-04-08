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

#include "QyValueHandler.h"
#include "QyValueTransfomer.h"
#include "QyStyleData.h"
#include "QyAbstractIndicator.h"
#include <QtWidgets/qstyleoption.h>

QT_BEGIN_NAMESPACE

class Q_WIDGETS_EXPORT QyStyleOption : public QStyleOptionComplex
{
public:
    enum StyleOptionType { Type = SO_ComplexCustomBase + 1 };
    enum StyleOptionVersion { Version = 1 };
    const QyBase::ValueVector   * valueDisplay;
    const StyleData             * styleData;
    QyStyleOption();
    QyStyleOption(const QyStyleOption &other) : QStyleOptionComplex(Version, Type) { *this = other; }

protected:
    QyStyleOption(int version);
};

QT_END_NAMESPACE

