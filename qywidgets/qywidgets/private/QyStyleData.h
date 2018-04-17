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

#include "QyEnums.h"

QT_BEGIN_NAMESPACE

struct StyleData {
    static constexpr int fracDegree = 16;     // 5760 (16 * 360).
    static constexpr int circleFracDegree = fracDegree * 360;
    static constexpr int maxPainterWidth = 8;
    static constexpr int minPainterWidth = 2;
    static constexpr int adjPainterWidth = 30;
    static constexpr int minSizeForText = 20; // TODO test
    static constexpr int minMargin = 2;

    static constexpr int normalStateColorAlpha = 255;
    static constexpr int remoteStateColorAlpha = 128;
    static constexpr int disableStateColorAlpha = 64;

    StyleData()
    : caption()
    , graphicStyle(Qy::GS_Rotary)
    , textBoxPlacement(Qy::TB_AutoTextBox)
    , subIndicatorStyle(Qy::SIS_Auto)
    , colorStyle(Qy::CS_Auto)
    , orientation(Qt::Horizontal)
    , sequenceOrientation(Qt::Horizontal)
    , textColor(128,128,128,255)
    , leftColor(0,255,255,255)
    , rightColor(255,128,128,255)
    , graphicsRect()
    , valueTextRect()
    , captionTextRect()
    , infoTextRect()
    , margins()
    , sizeHint(100, 100)
    , minimumSizeHint(50, 50)
    , slotSize(24*fracDegree)
    , arcBegin(270*fracDegree - slotSize)
    , painterWidth(2)
    , flags(0)
    {
    }

    void setColors( const QColor& leftc
        , const QColor& rightc
        , int enabledAlpha
        , int disabledAlpha
        )
    {
        leftColor = leftc;
        rightColor = rightc;
    }

    QString                 caption;

    Qy::GraphicStyle        graphicStyle;
    Qy::TextBoxPlacement    textBoxPlacement;
    Qy::SubIndicatorStyle   subIndicatorStyle;

    Qy::ColorStyle          colorStyle;
    Qt::Orientation         orientation;
    Qt::Orientation         sequenceOrientation; // for multidisplay

    QColor      textColor;
    QColor      leftColor;
    QColor      rightColor;

    QRect       graphicsRect;
    QRect       valueTextRect;
    QRect       captionTextRect;
    QRect       infoTextRect;
    QMargins    margins;

    QSize       sizeHint;
    QSize       minimumSizeHint;

    int         slotSize;
    int         arcBegin;
    int         painterWidth;
    int         fontHeight;
    uint        stateLedValue; // TODO check usability

    union {
        uint flags;
        struct
        {
            uint mirrored               : 1;    //
            uint invertedFlow           : 1;    // chenaged max and min position
            uint controllerIndicator    : 1;    // controller with additional indicator
            uint pressed                : 1;    // needed ?
            uint remoteControlled       : 1;

//            uint hovered        : 1;    // needed ?
//            uint clicked        : 1;    // needed ?
//            uint tracking       : 1;    // needed ?
        };
    };
};

QT_END_NAMESPACE
