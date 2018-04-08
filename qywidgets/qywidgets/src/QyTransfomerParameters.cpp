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

#include "QyTransfomerParameters.h"
#include "QyConsts.h"
#include <cmath>
#include <QtMath>
#include <QDebug>

namespace QyBase {

TransfomerParameters::TransfomerParameters()
:   minimum(0.0)
,   maximum(100.0)
,   mx(1.0)
,   my(1.0)
,   p0(0.0)
,   p1(1.0)
{}

void TransfomerParameters::initTransformParameters( double p0, double p1 )
{
    this->p0 = p0;
    this->p1 = p0;
}

namespace TransformLin {
    double slider2value( TransfomerParameters *thp, double val )
    {
        return thp->mx * val + thp->minimum;
    }
    int32_t value2slider( TransfomerParameters *thp, double val )
    {
        return ( val - thp->minimum ) / thp->mx;
    }
    bool setValueRange( TransfomerParameters *thp, double minimum, double maximum )
    {
        if( minimum >= maximum ) {
            return false;
        }
        thp->minimum = minimum;
        thp->maximum = maximum;
        thp->mx = ( maximum - minimum ) * rangeSliderInv;
        return true;
    }
} // end namespace TransformLin

namespace TransformExp2 {
    double slider2value( TransfomerParameters *thp, double val )
    {
        return std::exp2( val * thp->mx ) * thp->minimum;
    }
    int32_t value2slider( TransfomerParameters *thp, double val )
    {
        return std::log2( val / thp->minimum ) / thp->mx;
    }
    bool setValueRange( TransfomerParameters *thp, double minimum, double maximum )
    {
        if(( minimum <= 0.0 ) || ( minimum >= maximum )) {
            return false;
        }
        thp->minimum = minimum;
        thp->maximum = maximum;
        thp->mx = std::log2(maximum/minimum) * rangeSliderInv; // *1/log2(logk)
        return true;
    }
} // end namespace TransformExp2

namespace TransformSinPI2 {
    double slider2value( TransfomerParameters *thp, double val )
    {
        constexpr double cmx = M_PI_2 /  maximumSlider;
        return std::sin( val * cmx ) * thp->maximum;
    }
    int32_t value2slider( TransfomerParameters *thp, double val )
    {
        constexpr double cmy = maximumSlider / M_PI_2;
        return std::asin( val / thp->maximum ) * cmy;
    }
    bool setValueRange( TransfomerParameters *thp, double minimum, double maximum )
    {
        if( maximum <= 0.0 ) {
            return false;
        }
        thp->minimum = 0.0;
        thp->maximum = maximum;
        return true;
    }
} // end namespace TransformSinPI2

} // end namespace QyBase
