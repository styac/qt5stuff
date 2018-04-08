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

#include <cmath>
#include <cstdint>
#include <QDebug>

namespace qyc {


// slider value --- int: 0 .. (1<<30) -1
//  mapped by the painter to the arc/line
//  easy to check minimum, maximum, division by shift
//
//      map to double linear by y = minimum + x * range
//      range = (maximum-minimum)
//  setValue:   x = (y/range) - minimum
//  double: minimum, maximum, range, y
//  then log,exp,sin, ....

//  singleStep = 1/1024 up,down  30-10  --> 1<<20
//  pageStep = 1/128 page up,down       --> 1<<23
//  giantStep --->  shift page up down
//  tinyStep 1/8192 -- left,right       --> 1<<17
// home : zero (symmetric : 1/2) -- double click
// end - default value (settable mark -- shift end)

// how repeat work -- why is implemented in widget level


//double transfunc_direct_exp2( double x, CbData& cbdata );
//double transfunc_inverse_exp2( double x, CbData& cbdata );
//void setfunc_exp2( double minimum, double maximum, CbData& cbdata );

//// log10(x) == log2(x)/log2(10)
//double transfunc_direct_log2( double x, CbData& cbdata );
//double transfunc_inverse_log2( double x, CbData& cbdata );
//void setfunc_log2( double minimum, double maximum, CbData& cbdata );

//double transfunc_direct_sin( double x, CbData& cbdata );
//double transfunc_inverse_sin( double x, CbData& cbdata );
//void setfunc_sin( double minimum, double maximum, CbData& cbdata );

//double transfunc_direct_tan( double x, CbData& cbdata );
//double transfunc_inverse_tan( double x, CbData& cbdata );
//void setfunc_tan( double minimum, double maximum, CbData& cbdata );
class ValueHandler;
// power
typedef void (*FpSlider2value)  ( ValueHandler* );
typedef void (*FpValue2slider)  ( ValueHandler* );
typedef bool (*FpSetAllValues)  ( ValueHandler*, double, double );
//    typedef bool (*FpSetAllValues)  ( ValueHandler*, double, double, double, double ); // extra params

//    typedef void (*FpSlider2value) ( ValueHandler*, std::shared_ptr<UserData> );
//    typedef void (*FpValue2slider) ( ValueHandler*, std::shared_ptr<UserData> );
//    typedef bool (*FpSetAllValues) ( ValueHandler*, double, double, std::shared_ptr<UserData> );
//    static void slider2value_lin( ValueHandler*, void *userData = nullptr );
//    static void value2slider_lin( ValueHandler*, void *userData = nullptr );
//    static bool setAllValues_lin( ValueHandler*, double minimum, double maximum, void *userData = nullptr );

     void slider2value_lin( ValueHandler* );
     void value2slider_lin( ValueHandler* );
     bool setAllValues_lin( ValueHandler*, double minimum, double maximum );
//    static bool setAllValues_lin( ValueHandler*, double minimum, double maximum, double my, double dx );

     void slider2value_exp( ValueHandler* );
     void value2slider_exp( ValueHandler* );
//    static bool setAllValues_exp( ValueHandler*, double minimum, double maximum, double my, double dx );

class ValueHandler
{
public:
    static constexpr int32_t rangeSliderExp = 30;
    static constexpr int32_t rangeSlider = 1<<rangeSliderExp;
    static constexpr int32_t minimumSlider = 0;
    static constexpr int32_t maximumSlider = rangeSlider+1;
    static constexpr double rangeSliderInv = 1.0 / double(maximumSlider);
    static constexpr int32_t halfpointSlider = (rangeSlider/2)+1; // odd count

    static constexpr int32_t giantStepDiv = 3;
//    static constexpr int32_t minSingleStep = rangeSlider>>10;
//    static constexpr int32_t maxSingleStep = rangeSlider>>8;
//    static constexpr int32_t minPageStep = rangeSlider>>7;
//    static constexpr int32_t maxPageStep = rangeSlider>>5;

    ValueHandler();

    inline void init()
    {
        // init variables
    }

    inline bool reset()
    {
        auto resetPoint = minimumSlider;
        if( symmetric ) {
            resetPoint = halfpointSlider;
        }
        if( sliderValue == resetPoint ) {
            return false;
        }
        sliderValue = resetPoint;
        slider2value(this);
        return true;
    }
//    inline void registerFunctions( FpDirec direct, FpInv value2slider, FpSet setAllValues, void *userData )
//    this->userData = userData;

    inline void registerFunctions( FpSlider2value slider2value, FpValue2slider value2slider, FpSetAllValues setAllValues )
    {
        this->slider2value = slider2value;
        this->value2slider = value2slider;
        this->setAllValues = setAllValues;
        init();
    }
    inline double clampValue( double val ) const
    {
        if( val < minimum )
            return minimum;
        if( val > maximum )
            return maximum;
        return val;
    }
    inline int32_t clampSliderValue( int32_t val ) const
    {
        if( val < minimumSlider )
            return minimumSlider;
        if( val > maximumSlider )
            return maximumSlider;
        return val;
    }
    // returns true if changed
    inline bool setMinimum( double val )
    {
        if( val == minimum ) {
            return false;
        }
        minimum = val;
        return setAllValues( this, minimum, maximum );
    }
    // returns true if changed
    inline bool setMaximum( double val )
    {
        if( val == maximum ) {
            return false;
        }
        maximum = val;
        return setAllValues( this, minimum, maximum );
    }
    // returns true if changed
    inline bool setValue( double val )
    {
        if( val == value ) {
            return false;
        }
        auto oldv = value;
        value = clampValue(val);
        if( value == oldv ) {
            return false;
        }
        value2slider(this);
        return true;
    }
    inline double getValue() const
    {
        return value;
    }
    // return true if value was changed
    inline bool setSliderValue( int32_t val )
    {
        val = clampSliderValue( val );
        if( sliderValue == val ) {
            return false;
        }
        sliderValue = val;
        slider2value(this);
        return true;
    }
    inline bool addSliderValue( int32_t val )
    {
        return setSliderValue( val + sliderValue );
    }
    inline int32_t getSliderValue() const
    {
        return sliderValue;
    }
    inline int32_t getPaintValue( uint16_t paintValueRange ) const
    {
        return int32_t(( int64_t(sliderValue) * paintValueRange ) >> rangeSliderExp );
    }
    inline bool stepGiant( bool up )
    {
        if( up ) {
            auto diff = maximumSlider - sliderValue;
            return setSliderValue( diff <= pageStep ? maximumSlider : sliderValue + (diff >> giantStepDiv) );
        }
        return setSliderValue( sliderValue <= pageStep ? 0 : sliderValue - (sliderValue >> giantStepDiv) );
    }
    inline bool stepPage( bool up )
    {
        return addSliderValue( up ? pageStep : -pageStep );
    }
    inline bool stepSingle( bool up )
    {
        return addSliderValue( up ? singleStep : -singleStep );
    }
    inline bool stepTiny( bool up )
    {
        return addSliderValue( up ? tinyStep : -tinyStep );
    }
    inline bool stepBig( bool up )
    {
        return addSliderValue( up ? bigStep : -bigStep );
    }
    // valid: 0.02 ... 0.001
    inline bool setSingleStep( int val )
    {
        if( val < 1  ) {
            val = 1;
        } else if( val > 10 ) {
            val = 10;
        }
        if( val == singleStepInRange ) {
            return false;
        }
        // TODO> must be tested
        singleStepInRange = val;
        singleStep = (int64_t(val) << rangeSliderExp) / 1000;
        tinyStep = singleStep / 50;
        bigStep = singleStep * 3;
        return true;
    }

    // valid: 0.1 ... 0.02
    inline bool setPageStep( int val )
    {
        if( val < 20  ) {
            val = 20;
        } else if( val > 200 ) {
            val = 200;
        }
        if( val == pageStepInRange ) {
            return false;
        }
        pageStepInRange = val;
        pageStep = (int64_t(val) << rangeSliderExp) / 1000;
        return true;
    }

//    inline bool setSingleStep( int val )
//    {
//        if( val == singleStep ) {
//            return false;
//        }
//        if( val < minSingleStep ) {
//            singleStep = minSingleStep;
//            return true;
//        }
//        if( val > maxSingleStep ) {
//            singleStep = maxSingleStep;
//            return true;
//        }
//        singleStep = val;
//        return true;
//    }
//    inline bool setPageStep( int val )
//    {
//        if( val == pageStep ) {
//            return false;
//        }
//        if( val < minPageStep ) {
//            pageStep = minPageStep;
//            return true;
//        }
//        if( val > maxPageStep ) {
//            pageStep = maxPageStep;
//            return true;
//        }
//        pageStep = val;
//        return true;
//    }
    inline double getMinimum() const
    {
        return minimum;
    }
    inline double getMaximum() const
    {
        return maximum;
    }
    inline int32_t getPageStep() const
    {
        return pageStepInRange;
    }
    inline int32_t getSingleStep() const
    {
        return singleStepInRange;
    }
    inline bool isSymmetric() const
    {
        return bool(symmetric);
    }
    inline bool setSymmetric( bool val )
    {
        if(val == symmetric)
            return false;
        symmetric = val;
        return true;
    }

    FpSlider2value  slider2value;
    FpValue2slider  value2slider;
    FpSetAllValues  setAllValues;
    // std::shared_ptr<UserData> userData;

//private:
    double  mx;
    double  dx;
    double  my;
    double  dy;

    double  minimum;
    double  maximum;
    double  value;

    int32_t sliderValue;
    int32_t tinyStep;
    int32_t singleStep;
    int32_t bigStep;
    int32_t pageStep;
    int32_t singleStepInRange;
    int32_t pageStepInRange;
    uint    symmetric : 1;
};


}  // end qyc

