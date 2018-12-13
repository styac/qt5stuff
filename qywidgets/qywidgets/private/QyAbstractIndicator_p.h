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
#include "QyValueTransfomer.h"
#include <private/qwidget_p.h>
#include <private/qframe_p.h>

QT_BEGIN_NAMESPACE

class QyAbstractIndicatorPrivate : public QFramePrivate
{
    Q_DECLARE_PUBLIC(QyAbstractIndicator)

public:
    QyAbstractIndicatorPrivate( bool res0 = false );
    ~QyAbstractIndicatorPrivate();

    void recalculateStyleData( const QyAbstractIndicator * thp );
    int32_t                 id;         // may not be needed here but in controller
    int32_t                 groupIndex; // index in the groupvector // may not be needed here but in controller
    QColor                  stateOnColor;
    QColor                  stateOffColor;
    QColor                  remoteControlledColor;

    QyBase::ValueVector     valueVector;
    QyBase::ValueTransfomer indicatorTransformer;
    StyleDataIndicator      styleData;
};

QT_END_NAMESPACE

