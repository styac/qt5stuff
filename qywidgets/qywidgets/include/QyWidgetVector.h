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

#include <QtWidgets>
#include <QVector>

QT_BEGIN_NAMESPACE

// DOESN'T DELETE THE WIDGETS

template< class WidgetType >
class QyWidgetVector {
public:
    QyWidgetVector() = delete;
    inline QyWidgetVector( uint32_t vectorSize, QWidget * parent = 0 )
    :   wv()
    {
        for( uint32_t i = 0; i < vectorSize; ++ i ) {
            WidgetType * w = new WidgetType( parent );
            wv.push_back(w);
        }
    }

    ~QyWidgetVector()
    {
    }

    inline auto& get()
    {
        return wv;
    }

    inline const auto& get() const
    {
        return wv;
    }
    // add to layout
//    inline void addLayout( )
//    {

//    }

private:
    QVector<WidgetType> wv;
};

QT_END_NAMESPACE
