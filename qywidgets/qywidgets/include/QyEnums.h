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
#include "QyGlobal.h"
#include <QtWidgets/qwidget.h>

QT_BEGIN_NAMESPACE

class QYWIDGET_LIBSHARED_EXPORT Qy : private QWidget {
    Q_OBJECT

public:
    enum GraphicStyle : uint8_t {
        // single controller, display, multidisplay
        // controller   = vv[0]
        GS_NoGraphics,          // selects Qy_AutoDisplay
        GS_Slider,              // classic line
        GS_Rotary,               // classic circle
        GS_HalfRotary,           // half circle
        GS_Triangle,            // typical volume control
        GS_RoundLed,
        GS_SquareLed,


//        GS_TwinSlider   = 0x10,
//        GS_TwinHalfGauge,
//        GS_ConcentricGauge,
//        GS_ConcentricHalfGauge,

//        GS_GaugeLed     = 0x20,
//        GS_HalfGaugeLed,
//        GS_SliderLed,

        GS_MAX
    };

    Q_ENUM(GraphicStyle);

    enum TextBoxPlacement : uint8_t  {
        TB_NoTextBox,
        TB_AutoTextBox,
        TB_TopTextBox,         //
        TB_BottomTextBox,      //

        TB_MAX
    };

    Q_ENUM(TextBoxPlacement);

    enum ColorStyle : uint8_t  {
        CS_Auto,
        CS_Rainbow,

        CS_MAX
    };

    Q_ENUM(ColorStyle);

    // controller+value together or 2 values - vv.size must be 2
    // controller   = vv[0]
    // display      = vv[1]

    enum SubIndicatorStyle : uint8_t  {
        SIS_Auto,       // TwinSlider, ConcentricGauge, ConcentricHalfGauge
        SIS_RoundLed1,
        SIS_SquareLed1,

        SIS_MAX
    };

    Q_ENUM(SubIndicatorStyle);

    enum ValuePhysicalType : uint8_t  {
        VPT_Number,
        VPT_Time_Sec,
        VPT_Mass_Gram,
        VPT_Energy_Joule,
        VPT_Length_Meter,
        VPT_Frequency_Hertz,

        VPT_MAX,
    };

    Q_ENUM(ValuePhysicalType);

private:
    Qy() = delete;
    Qy(Qy&) = delete;
    Qy(Qy&&) = delete;
    Qy(const Qy&) = delete;
};

QT_END_NAMESPACE
