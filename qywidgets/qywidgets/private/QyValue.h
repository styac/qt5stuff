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

#include <QString>
#include <QVector>
#include <array>

namespace QyBase {

struct Value
{
    Value()
    :   value(0.0)
    ,   sliderValue(-1000)
    {}


    inline int32_t getPaintValue( uint16_t paintValueRange ) const
    {
        return int32_t(( int64_t( sliderValue) * paintValueRange + (1<<(rangeSliderExp-1)) ) >> rangeSliderExp );
    }

    double  value;
    QString valueString;
    QString suffix;
    int32_t sliderValue;
};


class ValueVector {
public:
    ValueVector()
    : decimalPlaces(4)
    {
        setSize(1);
    }
    inline uint16_t getSize() const
    {
        return vv.size();
    }
    inline uint16_t setSize( uint16_t val )
    {
        if( val < 1 ) {
            return vv.size();
        }
        vv.resize(val);
        for( auto& v : vv) {
            v.value = 0.0;
            v.valueString = "0";
            v.sliderValue = 0;
            v.suffix.clear();
//            v.suffix.clear();
        }
        return vv.size();
    }

    inline bool check( uint8_t index ) const
    {
        return vv.size() > index;
    }

    inline uint32_t getDecimalPlaces() const
    {
        return decimalPlaces;
    }

    inline void setDecimalPlaces(uint32_t val)
    {
        decimalPlaces = val;
    }

    inline bool set(double val, int32_t sliderVal, uint8_t index)
    {
        auto& v = vv[index];
        if( val == v.value && (sliderVal == v.sliderValue)) {
            return false;
        }
        v.value = val;
        v.sliderValue = sliderVal;
        v.valueString.setNum( val, 'f', decimalPlaces );
        return true;
    }

    inline auto getValueString(uint8_t index) const
    {
        return vv[index].valueString;
    }

    inline int32_t getPaintValue( uint16_t paintValueRange, uint8_t index ) const
    {
        return vv[index].getPaintValue(paintValueRange);
    }

    inline bool setSuffix( const QString& val, uint8_t index )
    {
        if( vv[index].suffix == val ) {
            return false;
        }
        vv[index].suffix = val;
        return true;
    }

    inline const QString& getSuffix( uint8_t index ) const
    {
        return vv[index].suffix;
    }

    QVector<Value> vv;
    uint32_t decimalPlaces;
};


} // end namespace Qy


