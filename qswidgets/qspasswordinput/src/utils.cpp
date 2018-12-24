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

#include "utils.h"
#include <QClipboard>
#include <QApplication>

//
// WARNING: Clipboard history (Klipper, etc) IS NOT CLEARED
//
bool clipboardPaste( PWstr& text )
{
    QClipboard *clipboard = QApplication::clipboard();
    const QString& str = clipboard->text();
    if( str.length() == 0 ) {
        return false;
    }
    {
        // TODO: check normalize !!! - check password managers
        const QByteArray utf8val = str.toUtf8(); // will be shared
        text.clear();
        text.insert(std::begin(text), std::begin(utf8val), std::end(utf8val));
        secureClear( utf8val );
    }
    // clear clipboard
    secureClear(str);
    clipboard->clear();
    return true;
}

