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

#include <QString>
#include <QByteArray>
#include <string>
#include <iostream>
#include <vector>

using utf8string = std::vector<char>; // no data sharing - COW

template<typename T>
inline void secureClear( const T& str )
{
    std::size_t len = std::size_t(str.capacity()) * sizeof(typename T::value_type);
    volatile char * vpbegin = const_cast<volatile char *>((const char *)str.data());
//    std::cout
//        << "\nsecureClear len:" << len
//        << " typelen:" << sizeof(typename T::value_type)
//        << " ptr:" << (void *)vpbegin
//        << std::endl;
    while( len-- > 0 ) {
//        std::cout
//            << " " << std::hex << uint16_t(*vpbegin);
        *vpbegin++ = 0;
    }
//    std::cout << std::endl;
}

struct PWstr : public utf8string
{
    PWstr() = delete;

    inline PWstr(size_t res)
    : utf8string()
    {
        this->reserve(res);
    }

    inline ~PWstr()
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

inline std::ostream &operator <<(std::ostream &os, const PWstr &v) {
    for( auto c : v ) {
        os << c;
    }
   return os;
}

bool clipboardPaste( PWstr& text );
