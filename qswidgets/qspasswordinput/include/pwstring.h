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

#include "secureclear.h"

#include <iostream>
#include <vector>

using utf8string = std::vector<char>;

struct PWstring : public utf8string
{
    PWstring() = delete;

    inline PWstring(size_t res)
    : utf8string()
    {
        this->reserve(res);
    }

    inline ~PWstring()
    {
        secureClear(*this);
    }

    inline void shred()
    {
        secureClear(*this);
        utf8string::clear();
    }

    void trimLastUtf8()
    {
        switch(size()) {
        case 0:
            return;
        case 1:
            utf8string::clear();
            return;
        }
        uint8_t c = back();
        pop_back();
        if( ! (c & 0x80) ) {
            return;
        }
        // utf8
        while( size() > 0 ) {
            uint8_t c = back() & 0xC0;
            pop_back();
            if( c == 0xC0u ) {
                return;
            }
        }
    }

    size_t charCount() const
    {
        size_t l = size();
        const uint8_t *p = (const uint8_t *) data();
        for( size_t i=l; i>0; --i ) {
            if( (*p++ & 0xC0 ) == 0x80 ) {
                // substract cont chars 0b10xxxxxx
                --l;
            }
        }
        return l;
    }
};

inline std::ostream &operator << ( std::ostream &os, const PWstring &v ) {
    for( auto c : v ) {
        os << c;
    }
   return os;
}

