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

#include "QyStyleData.h"
#include "QyExtraState.h"
#include <private/qwidget_p.h>

QT_BEGIN_NAMESPACE

// button style
//  square_1_1
//  square_1_2
//  square_2_1
//  round

class QyAbstractButtonPrivate : public QWidgetPrivate
{
    Q_DECLARE_PUBLIC(QyAbstractButton)

public:
    QyAbstractButtonPrivate();
    ~QyAbstractButtonPrivate();

//    void recalculateStyleData( const QyAbstractButton * thp );
    int32_t         id;
    int32_t         groupIndex;
    QColor          stateOnColor;
    QColor          stateOffColor;
    QColor          remoteControlledColor;

    QString         text;
    int             ledState;
    StyleDataButton styleData;
    QyExtraState    extraState;
    union {
        uint8_t flags;
        struct
        {
            uint8_t state                  : 1;
            uint8_t hoverable              : 1; // send entered,left on hoverEvent
            // if false then push button
            //  push> state = true
            //  release> state = false
            // else
            //  push> state ^= state
            //
            uint8_t toggleable             : 1;
            uint8_t exclusive              : 1;
            uint8_t buttonGroup            : 1; // group
        };
    };
};

QT_END_NAMESPACE

