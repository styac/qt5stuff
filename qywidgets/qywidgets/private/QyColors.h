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

#include <array>
#include <QColor>

namespace QyBase {

class Rainbow {
public:
    static constexpr uint8_t sizeExp = 5;
    static constexpr uint8_t size = 1<<sizeExp;    // 128?
    static constexpr uint8_t maxHue = 240;
    static auto& getInstance()
    {
        static Rainbow instance;
        return instance;
    }
    inline void set0( const QColor& val )
    {
        //rainbow[0] = QWidget::palette().color(QWidget::backgroundRole());
        rainbow[0] = val;
    }
    inline const QColor& get( int32_t index ) const
    {
        // take the highest bits? of 30
        if( index < 0 ) {
            return rainbow[0];
        } else if( index > size-1 ) {
            return rainbow[size-1];
        }
        return rainbow[index];
    }
private:
    Rainbow();
    std::array<QColor,size> rainbow;
};

// for audio volume
//  reference level : 14/32 -- 0 db 0..14 - bluish ??? TODO
//  0..3 yellow
//  3..6 orange
//  6... red
// -x .. 0 deep blue ... light blue

class VolumeColors {
public:
    static constexpr uint16_t size = 32;
    static constexpr uint16_t maxHue = 240;
    static const auto& getInstance()
    {
        static VolumeColors instance;
        return instance;
    }
    inline void set0( const QColor& val )
    {
        //rainbow[0] = QWidget::palette().color(QWidget::backgroundRole());
        rainbow[0] = val;
    }
    inline const QColor& get( uint16_t index ) const
    {
        if( index > size-1) {
            return rainbow[size-1];
        }
        return rainbow[index];
    }
private:
    VolumeColors()
    {
        for( uint8_t i=1; i < size-1; ++i  ) {
            rainbow[i].setHsl( maxHue * (size-i-2) / (size-1), 255, 255 ) ;
        }
        rainbow[0].setHsl(0,0,16);
        rainbow[size-1].setHsl(0,255,255);
    }
    std::array<QColor,size> rainbow;
};

} // end namespace Qy
