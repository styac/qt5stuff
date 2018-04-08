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
#include <string>

namespace QyBase {

struct  TransfomerParameters  {
    void initTransformParameters( double, double );
    typedef double  (*FpSlider2value) ( TransfomerParameters*, double );
    typedef int32_t (*FpValue2slider) ( TransfomerParameters*, double );
    typedef bool    (*FpSetMinMax)    ( TransfomerParameters*, double, double );

    TransfomerParameters();

    double  minimum;
    double  maximum;
    double  mx;
    double  my;

    // optional help parameters
    double  p0;
    double  p1;
};


namespace TransformLin {
double   slider2value(   TransfomerParameters*, double );
int32_t  value2slider(   TransfomerParameters*, double );
bool     setValueRange(  TransfomerParameters*, double minimum, double maximum );
} // end namespace TransformLin

namespace TransformExp2 {
double   slider2value(   TransfomerParameters*, double );
int32_t  value2slider(   TransfomerParameters*, double );
bool     setValueRange(  TransfomerParameters*, double minimum, double maximum );
} // end namespace TransformExp2

namespace TransformSinPI2 {
double   slider2value(   TransfomerParameters*, double );
int32_t  value2slider(   TransfomerParameters*, double );
bool     setValueRange(  TransfomerParameters*, double minimum, double maximum );
} // end namespace TransformSinPI2

} // end namespace QyBase
