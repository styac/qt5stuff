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

#include "QyValueTransfomer.h"
#include <QDebug>

namespace QyBase {

ValueTransfomer::ValueTransfomer( ValueVector& vvr, bool r0 )
:   TransfomerParameters()
,   slider2value(TransformLin::slider2value)
,   value2slider(TransformLin::value2slider)
,   setValueRange(TransformLin::setValueRange)
,   vvref(vvr)
,   symmetric(true) // defult false, but must be set explicit
,   reserved0(r0)
{
    setValueRange(this, 0.0, 100.0);
    init();
       qDebug() << "--ctor--  ValueTransfomer";
}

bool ValueTransfomer::init()
{
    bool res = true;
    for( auto& vref : vvref.vv ) {
        vref.value = 0.0;
        vref.sliderValue = 0;
        if( setValueRange( this, minimum, maximum )) {
            vref.value = slider2value(this, vref.sliderValue );
//            vref.makeValueString(inde);
        } else {
            res = false;
        }
    }
    return res;
}

bool ValueTransfomer::registerTransformFunctions( FpSlider2value slider2value, FpValue2slider value2slider, FpSetMinMax setValueRange )
{
    if(     ( slider2value == nullptr )
        ||  ( value2slider == nullptr )
        ||  ( setValueRange == nullptr )) {
        return false;
    }
    this->slider2value = slider2value;
    this->value2slider = value2slider;
    this->setValueRange = setValueRange;
    return init();
}

bool ValueTransfomer::reset( uint8_t index )
{
    auto resetPoint = symmetric ? halfpointSlider : minimumSlider;
    return vvref.set(slider2value(this, resetPoint), resetPoint, index);
}

} // end namespace QyBase

