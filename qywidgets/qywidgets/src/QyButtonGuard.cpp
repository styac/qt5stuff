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

#include "QyButtonGuard.h"

QT_BEGIN_NAMESPACE

QyButtonGuard::QyButtonGuard( QWidget *parent)
: toggledlast(-1)
, maxId(0)
{
}

QyButtonGuard::~QyButtonGuard()
{
}

void QyButtonGuard::toggled( int id, int groupIndex )
{
    if( groupIndex == toggledlast ) {
        return;
    }
    if( (groupIndex < 0 ) || ( groupIndex >= maxId ) ) {
        return;
    }
    if( toggledlast < 0 ) {
        toggledlast = groupIndex;
        return;
    }
    if( notifyToggled( id, groupIndex ) ) {
        toggledlast = groupIndex;
    }
}

QT_END_NAMESPACE

