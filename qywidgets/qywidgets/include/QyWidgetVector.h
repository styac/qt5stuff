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
#include <QGridLayout>
#include <QBoxLayout>


QT_BEGIN_NAMESPACE

// DOESN'T DELETE THE WIDGETS

// need a external widget>
// window->setLayout(layout);
template< class WidgetType, class LayoutType >
class QyWidgetVector {
public:
   ~QyWidgetVector()
    {
        delete l;
    }

    inline auto& widgets()
    {
        return wv;
    }

    inline const auto& widgets() const
    {
        return wv;
    }

    inline auto& layout()
    {
        return l;
    }

    inline const auto& layout() const
    {
        return l;
    }

    inline const QSize& applySize( const QSize& s )
    {
        for( auto& v : wv ) {
            v->setFixedSize(s);
        }
        int margin = 8; // TODO get margin
        if( y == 0 ) {
            thisSize.setWidth(s.width()+margin);
        } else {
            thisSize.setWidth(y*s.width()+margin);
        }
        thisSize.setHeight(x*s.height()+margin);
        return thisSize;
    }

    inline const QSize& size() const
    {
        return thisSize;
    }

    inline void applyId( int idv, int ide, bool rowSequence = true  )
    {
        if( rowSequence || (y==0) ) {
            for( auto& v : wv ) {

                // TEST BEGIN
                QString cap( QString("%0").arg(idv) );
                v->setCaption( cap );
                // TEST END


                v->setUserEventValue(ide++);
                v->setValueId(idv++);

            }
            return;
        }
        // TODO make coloumn sequence
        for( auto& v : wv ) {
            v->setUserEventValue(ide++);
            v->setValueId(idv++);
        }
    }

protected:
    QyWidgetVector() = delete;
    inline QyWidgetVector( int xp, int yp )//, QWidget *parent )
    :   wv()
    ,   l()
    ,   thisSize()
    ,   x(xp==0 ? 1 : xp)
    ,   y(yp)
    {}

    QVector<WidgetType *>   wv;
    LayoutType            * l;
    QSize                   thisSize;
    const int x;
    const int y;
};

template< class WidgetType >
class QyWidgetVectorGrid : public QyWidgetVector<WidgetType, QGridLayout> {
public:
    using LayoutType = QGridLayout;
    using ParentType = QyWidgetVector<WidgetType, LayoutType>;
    QyWidgetVectorGrid() = delete;
    inline QyWidgetVectorGrid( uint32_t xp, uint32_t yp, QWidget *parent )
    : ParentType(xp,yp)
    {
        ParentType::l = new LayoutType();
        if( xp == 0 ) {
            xp = 1;
        }
        if( yp == 0 ) {
            yp = 1;
        }
        for( uint32_t xi = 0; xi < xp; ++ xi ) {
            for( uint32_t yi = 0; yi < yp; ++ yi ) {
                WidgetType * w = new WidgetType( parent );
                ParentType::wv.push_back(w);
                ParentType::l->addWidget(w,xi,yi);
            }
        }
        parent->setLayout(ParentType::l);
    }
};

template< class WidgetType >
class QyWidgetVectorBox : public QyWidgetVector<WidgetType, QBoxLayout> {
public:
    using LayoutType = QBoxLayout;
    using ParentType = QyWidgetVector<WidgetType, LayoutType>;
    QyWidgetVectorBox() = delete;
    inline QyWidgetVectorBox( uint32_t xp, LayoutType::Direction direction, QWidget *parent )
    : ParentType(xp,0)
    {
        ParentType::l = new LayoutType(direction);
        if( xp == 0 ) {
            xp = 1;
        }

        for( uint32_t xi = 0; xi < xp; ++ xi ) {
            WidgetType * w = new WidgetType( parent );
            ParentType::wv.push_back(w);
            ParentType::l->addWidget(w,xi);
        }
        parent->setLayout(ParentType::l);
    }
};


QT_END_NAMESPACE
