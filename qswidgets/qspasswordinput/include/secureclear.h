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

#include <iostream>

template<typename T>
inline void secureClear( const T& str )
{
    std::size_t len = std::size_t(str.capacity()) * sizeof(typename T::value_type);
    volatile char * vpbegin = const_cast<volatile char *>((const char *)str.data());
//    std::cout << "\nsecureClear len:" << len
//        << " typelen:" << sizeof(typename T::value_type)
//        << " ptr:" << (void *)vpbegin
//        << std::endl;
    while( len-- > 0 ) {
//        std::cout << " " << std::hex << uint16_t(*vpbegin);
        *vpbegin++ = 0;
    }
//    std::cout << std::endl;
}

