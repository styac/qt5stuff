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

#include "QyConsts.h"
#include <QDebug>

namespace QyBase {

enum class STEPS : uint8_t {
    STEP_TINY,
    STEP_TINY_PLUS,
    STEP_SINGLE,
    STEP_SINGLE_PLUS,
    STEP_PAGE,
};

constexpr uint STEP_ARRAY_SIZE = uint8_t(STEPS::STEP_PAGE) + 1;

class ValueHandler
{
public:
    ValueHandler()
    {
        setSingleStep(1);
        setPageStep(1);
    }

    // in the rate of the range
    //  val : 1..10 --
    inline void setSingleStep( int val )
    {
        const auto v = std::min(10, std::max(1,val));
        steps[ uint8_t(STEPS::STEP_SINGLE) ] = (v * rangeSlider) / 1000;
        steps[ uint8_t(STEPS::STEP_TINY) ] = steps[ uint8_t(STEPS::STEP_SINGLE) ] / 50;
        steps[ uint8_t(STEPS::STEP_TINY_PLUS) ] = steps[ uint8_t(STEPS::STEP_TINY )] * 6.666f;
        steps[ uint8_t(STEPS::STEP_SINGLE_PLUS) ] = steps[ uint8_t(STEPS::STEP_SINGLE) ] * 6.666f;
    }

    // in the rate of the range
    //  val : 1..10
    inline void setPageStep( int val )
    {
        const auto v = std::min(10, std::max(1,val));
        steps[ uint8_t(STEPS::STEP_PAGE) ] = (v * rangeSlider) / 100;
    }
    inline int32_t getPageStep() const
    {
        return (steps[ uint8_t(STEPS::STEP_PAGE) ] * 1000) >> rangeSliderExp;
    }
    inline int32_t getSingleStep() const
    {
        return (steps[ uint8_t(STEPS::STEP_SINGLE) ] * 100) >> rangeSliderExp;
    }
    // must be called by
    //        STEP_TINY,            left/right arrow -- smallest mouse step
    //        STEP_TINY_PLUS,       shift left/right arrow -- small mouse step
    //        STEP_SINGLE,          up/down arrow -- medium  mouse step
    //        STEP_SINGLE_PLUS,     shift up/down arrow -- bigger mouse step
    //        STEP_PAGE,            page up down -- big mouse step
    //              GIANT -- doesn use this

    inline int32_t getStepValue( STEPS stepType ) const
    {
        return steps[ uint8_t(stepType) ];
    }

protected:
    int32_t steps[ STEP_ARRAY_SIZE ];
};

}  // end Qy

