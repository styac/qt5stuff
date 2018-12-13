﻿#pragma once

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

#include "QyAbstractController.h"
#include "QyValueHandler.h"
#include "QyAbstractIndicator_p.h"
#include "QyExtraState.h"

QT_BEGIN_NAMESPACE

class QyAbstractControllerPrivate : public QyAbstractIndicatorPrivate
{
    Q_DECLARE_PUBLIC(QyAbstractController)

public:
    QyAbstractControllerPrivate();
    ~QyAbstractControllerPrivate();

    void setSteps(int single, int page);
    bool valueFromPoint(int val);

    QyBase::ValueHandler    valueHandler;
    QyBase::ValueTransfomer controllerTransformer;

    int     lastPosition;
    int     remoteControlledColorAlpha;

    Qy::ValuePhysicalType   valuePhysicalType;
    QyExtraState            extraState;

    union {
        uint8_t flags;
        struct
        {
            uint8_t emitSliderValue        : 1;
            uint8_t invertSetSliderPos     : 1;
            uint8_t invertEmitSliderPos    : 1;
            uint8_t pressed                : 1;
        };
    };
};

QT_END_NAMESPACE

