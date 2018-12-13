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
    static constexpr int normalStateColorAlpha = 255;
    static constexpr int remoteStateColorAlpha = 128;
    static constexpr int disableStateColorAlpha = 64;
    StyleData()
    : sizeHint(100, 100)
    , minimumSizeHint(50, 50)

//    : stateOnColor(0,255,255,255)
//    , stateOffColor(255,128,128,255)
    {

    }
    QSize       sizeHint;
    QSize       minimumSizeHint;

//    void setColors( const QColor& stateOn, const QColor& stateOff )
//    {
//        stateOnColor = stateOn;
//        stateOffColor = stateOff;
//    }
//    QColor      stateOnColor;
//    QColor      stateOffColor;
//    QSize       sizeHint;
//    QSize       minimumSizeHint;
};

struct StyleDataIndicator : public StyleData {
    static constexpr int fracDegree = 16;     // 5760 (16 * 360).
    static constexpr int circleFracDegree = fracDegree * 360;
    static constexpr int maxPainterWidth = 8;
    static constexpr int minPainterWidth = 2;
    static constexpr int adjPainterWidth = 30;
    static constexpr int minSizeForText = 20; // TODO test
    static constexpr int minMargin = 2;


    StyleDataIndicator()
    : StyleData()
    , caption()
    , graphicStyle(Qy::GSI_Rotary)
    , textBoxPlacement(Qy::TB_AutoTextBox)
    , subIndicatorStyle(Qy::SIS_Auto)
    , colorStyle(Qy::CS_Auto)
    , orientation(Qt::Horizontal)
    , sequenceOrientation(Qt::Horizontal)
    , textColor(128,128,128,255)
    , stateOnColor(0,255,255,255)
    , stateOffColor(255,128,128,255)
    , graphicsRect()
    , valueTextRect()
    , captionTextRect()
    , infoTextRect()
    , margins()
    , slotSize(24*fracDegree)
    , arcBegin(270*fracDegree - slotSize)
    , painterWidth(2)
    , flags(0)
    {
    }

    void setColors( const QColor& leftc, const QColor& rightc )
    {
        stateOnColor = leftc;
        stateOffColor = rightc;
    }

    QString                 caption;

    Qy::GraphicStyleIndicator        graphicStyle;
    Qy::TextBoxPlacement    textBoxPlacement;
    Qy::SubIndicatorStyle   subIndicatorStyle;

    Qy::ColorStyle          colorStyle;
    Qt::Orientation         orientation;
    Qt::Orientation         sequenceOrientation; // for multidisplay

    QColor      textColor;
    QColor      stateOnColor;
    QColor      stateOffColor;

    QRect       graphicsRect;
    QRect       valueTextRect;
    QRect       captionTextRect;
    QRect       infoTextRect;
    QMargins    margins;


    int         slotSize;
    int         arcBegin;
    int         painterWidth;
    int         fontHeight;
    // 0 = off
    // 1 = red
    // 2 = orange
    // 3 = yellow
    // 4 = green
    // 5 = turqouise
    // 6 = blue
    // 7 = white
    // TODO property, display
    uint8_t     stateLeftLedValue; // TODO check usability
    uint8_t     stateRightLedValue; // TODO check usability

    union {
        uint16_t flags;
        struct
        {
            uint16_t mirrored               : 1;    //
            uint16_t invertedFlow           : 1;    // chenaged max and min position
            uint16_t controllerIndicator    : 1;    // controller with additional indicator
            uint16_t pressed                : 1;    // needed ?
            uint16_t remoteControlled       : 1;// TODO remove

//            uint hovered        : 1;    // needed ?
//            uint clicked        : 1;    // needed ?
//            uint tracking       : 1;    // needed ?
        };
    };
};

struct StyleDataButton : public StyleData {
    static constexpr int maxPainterWidth = 8;
    static constexpr int minPainterWidth = 2;
    static constexpr int adjPainterWidth = 30;
    static constexpr int minSizeForText = 20; // TODO test
    static constexpr int minMargin = 2;


    StyleDataButton()
    : StyleData()
    , stateColor(128,128,128,255)
//    , caption()
//    , graphicStyle(Qy::GSI_Rotary)
//    , textBoxPlacement(Qy::TB_AutoTextBox)
//    , subIndicatorStyle(Qy::SIS_Auto)
//    , colorStyle(Qy::CS_Auto)
//    , orientation(Qt::Horizontal)
//    , sequenceOrientation(Qt::Horizontal)
//    , textColor(128,128,128,255)
    , graphicsRect()
//    , valueTextRect()
//    , captionTextRect()
//    , infoTextRect()
    , margins()
//    , slotSize(24*fracDegree)
//    , arcBegin(270*fracDegree - slotSize)
//    , painterWidth(2)
    , flags(0)
    {
    }


//    QString                 caption;

    QColor                  stateColor;
    Qy::GraphicStyleButton  graphicStyle;
//    Qy::TextBoxPlacement    textBoxPlacement;
//    Qy::SubIndicatorStyle   subIndicatorStyle;

//    Qy::ColorStyle          colorStyle;
//    Qt::Orientation         orientation;
//    Qt::Orientation         sequenceOrientation; // for multidisplay

//    QColor      textColor;

    QRect       graphicsRect;
//    QRect       valueTextRect;
//    QRect       captionTextRect;
//    QRect       infoTextRect;
    QMargins    margins;

//    int         slotSize;
//    int         arcBegin;
//    int         painterWidth;
//    int         fontHeight;

    union {
        uint16_t flags;
        struct
        {
            uint16_t state       : 1;// TODO remove
            uint16_t remoteControlled       : 1;// TODO remove
        };
    };
};

QT_END_NAMESPACE
