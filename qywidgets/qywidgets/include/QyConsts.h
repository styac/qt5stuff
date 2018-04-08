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

#include <cstdint>

namespace QyBase {
    constexpr int32_t rangeSliderExp = 30;
    constexpr int32_t rangeSlider = 1<<rangeSliderExp;
    constexpr int32_t minimumSlider = 0;
    constexpr int32_t maximumSlider = rangeSlider;
    constexpr double rangeSliderInv = 1.0 / double(maximumSlider);
    constexpr int32_t halfpointSlider = (rangeSlider/2);
    constexpr int32_t giantStepDiv = 3;
}

