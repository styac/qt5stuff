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

// to display a value like with the controller

#include "QyValue.h"
#include "QyTransfomerParameters.h"
#include "QyTypes.h"
#include <QDebug>

namespace QyBase {

class ValueTransfomer : public TransfomerParameters {
public:

    ValueTransfomer() = delete;
    ValueTransfomer( ValueVector& vvr, bool r0 = false );

    bool registerTransformFunctions( FpSlider2value slider2value, FpValue2slider value2slider, FpSetMinMax setValueRange );
    bool reset( uint8_t index=0 );
    bool init();

    inline double clampValue( double val ) const
    {
        if( val <= minimum )
            return minimum;
        if( val >= maximum )
            return maximum;
        return val;
    }

    inline bool setMinimum( double val )
    {
        return setValueRange( this, val, maximum );
    }

    inline bool setMaximum( double val )
    {
        return setValueRange( this, minimum, val );
    }

    inline bool setRange( double min, double max )
    {
        if( min >= max ) {
            return false;
        }
        if( ! setValueRange( this, min, max ) ) {
            return false;
        }

        uint digits = 1;
        if( max < 100.0 ) {
            digits = 2;
        } else if( max < 10.0 ) {
            digits = 3;
        } else if( max < 1.0 ) {
            digits = 4;
        }
        qDebug() << " digits: " << digits << " max " << max;

        vvref.setDecimalPlaces(digits);
        return true;
    }

    // returns true if changed
    inline bool setValue( double val, uint8_t index )
    {
        val = clampValue(val);
        return vvref.set(val, value2slider(this, val), index);
    }

    inline bool setValue( const QyBase::ValueIO& val )
    {
        int ch = 0;
        const std::size_t maxInd = std::min( val.size(), vvref.vv.size() );
        const std::size_t minInd = reserved0 ? 1 : 0;
        for( auto i=minInd; i<maxInd; ++i ) {
            ch += setValue( val[i], i );
        }
        return ch > 0;
    }

    inline double getValue( uint8_t index ) const
    {
        return vvref.vv[index].value;
    }

    inline ValueIO getValue() const
    {
        ValueIO val;
        for( auto& v : vvref.vv ) {
            val.push_back(v.value);
        }
        return val;
    }

    inline int32_t getSliderValue( uint8_t index ) const
    {
        return vvref.vv[index].sliderValue;
    }

    inline bool recalculate( uint8_t index )
    {
         auto val = getSliderValue(index);
         return vvref.set(slider2value(this, val), val, index);
    }

    inline double getMinimum() const
    {
        return minimum;
    }
    inline double getMaximum() const
    {
        return maximum;
    }
    inline const QString& getValueString( uint8_t index ) const
    {
        return vvref.vv[index].valueString;
    }

// 0..15 highest 4 bits of sliderValue ( 6 db * 16 = 96 )
//---> color table

    inline int32_t getRange( uint8_t range, uint8_t index ) const
    {
        return (vvref.vv[index].sliderValue>>(range & 0x1F));
    }
    inline bool getSymmetric() const
    {
        return symmetric;
    }
    inline bool setSymmetric( bool val )
    {
        if( val == symmetric ) {
            return false;
        }
        symmetric = val;
        return true;
    }

    // internal ctor init - true for controller false for display
    // for controller: vv[0] -- controlled value
    inline void setReserved0( bool val )
    {
        reserved0 = val;
    }


    inline bool setSliderValue( int32_t val, uint8_t index )
    {
        val = clampSliderValue( val );
        return vvref.set(slider2value(this, val), val, index);
    }

    inline int32_t clampSliderValue( int32_t val ) const
    {
        if( val < minimumSlider )
            return minimumSlider;
        if( val > maximumSlider )
            return maximumSlider;
        return val;
    }

    inline bool addSliderValue( int32_t val, uint8_t index  )
    {
        return setSliderValue( val + vvref.vv[index].sliderValue, 0 );
    }

    inline bool stepGiant( int stepValue )
    {
        if( stepValue > 0 ) {
            auto diff = maximumSlider - vvref.vv[0].sliderValue;
            return setSliderValue( diff <= stepValue ? maximumSlider : vvref.vv[0].sliderValue + (diff >> giantStepDiv), 0 );
        }
        return setSliderValue( vvref.vv[0].sliderValue <= -stepValue ? 0 : vvref.vv[0].sliderValue - (vvref.vv[0].sliderValue >> giantStepDiv), 0 );
    }

    inline int32_t getSliderMinimum() const
    {
        return minimumSlider;
    }

    inline int32_t getSliderMaximum() const
    {
        return maximumSlider;
    }

protected:
    FpSlider2value  slider2value;
    FpValue2slider  value2slider;
    FpSetMinMax     setValueRange;
    ValueVector&    vvref;

    uint            symmetric : 1;
    uint            reserved0 : 1;  // for controller
};

}  // end qyc

