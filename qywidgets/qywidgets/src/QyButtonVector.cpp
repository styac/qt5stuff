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

#if 0
#include "QyButtonVector.h"

QT_BEGIN_NAMESPACE

QyButtonVectorGrid::~QyButtonVectorGrid()
{
}


QyButtonVectorGrid::QyButtonVectorGrid( uint16_t rowp, uint16_t colp, bool colMajor, const QString& objectNameBase,
        const StringVectorType *rowLabels, const StringVectorType *colLabels )
: BaseType(rowp,colp)
{
    BaseType::l = new LayoutType();
    if( rowp == 0 ) {
        rowp = 1;
    }
    if( colp == 0 ) {
        colp = 1;
    }
    uint16_t row0 = 0;
    uint16_t col0 = 0;
    if(( colLabels != nullptr ) && ( colLabels->size() >= colp )) {
        BaseType::useColLabels = true;
    }
    if(( rowLabels != nullptr ) && ( rowLabels->size() >= rowp )) {
        BaseType::useRowLabels = true;
        ++col0;
        ++colp;
    }
    if( BaseType::useColLabels ) {
        ++row0;
        ++rowp;
        uint16_t labi = 0;
        for( uint16_t col = col0; col < colp; ++col, ++labi ) {
            auto * w = new QLabel( colLabels->value(labi) );
            w->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
            w->setObjectName(QString("%0_colLabel_%1").arg( objectNameBase ).arg(labi));
            w->setWordWrap(true);
            w->adjustSize();
            BaseType::l->addWidget(w,0,col);
            if( BaseType::colLabelHeight < w->height() ) {
                BaseType::colLabelHeight = w->height();
            }
        }
    }

    if( BaseType::useRowLabels ) {
        uint16_t labi = 0;
        for( uint16_t row = row0; row < rowp; ++row, ++labi ) {
            auto * w = new QLabel( rowLabels->value(labi) );
            w->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
            w->setObjectName(QString("%0_rowLabel_%1").arg( objectNameBase ).arg(labi));
            w->setWordWrap(true);
            w->adjustSize();
            BaseType::l->addWidget(w,row,0);
            if( BaseType::rowLabelWidth < w->width() ) {
                BaseType::rowLabelWidth = w->width();
            }
        }
    }

    uint16_t obni = 0;
    if( colMajor ) {
        for( uint16_t col = col0; col < colp; ++col ) {
            for( uint16_t row = row0; row < rowp; ++row, ++obni ) {
                auto * w = new WidgetType();
                w->setObjectName(QString("%0_%1").arg( objectNameBase ).arg(obni));
                // setAccessibleName(const QString &name)
                BaseType::wv.push_back(w);
                BaseType::l->addWidget(w,row,col);
            }
        }
    } else {
        for( uint16_t row = row0; row < rowp; ++row ) {
            for( uint16_t col = col0; col < colp; ++col, ++obni ) {
                auto * w = new WidgetType();
                w->setObjectName(QString("%0_%1").arg( objectNameBase ).arg(obni));
                // setAccessibleName(const QString &name)
                BaseType::wv.push_back(w);
                BaseType::l->addWidget(w,row,col);
            }
        }
    }
}

QyButtonVectorBox::~QyButtonVectorBox()
{
}

QyButtonVectorBox::QyButtonVectorBox( uint16_t rowp, LayoutType::Direction direction,
    const QString& objectNameBase,
    const StringVectorType *rowLabels
)
: BaseType(rowp,0)
{
    BaseType::l = new LayoutType(direction);
    if( rowp == 0 ) {
        rowp = 1;
    }

    for( uint16_t xi = 0; xi < rowp; ++ xi ) {
        WidgetType * w = new WidgetType();
        w->setObjectName(QString("%0_%1").arg( objectNameBase ).arg(xi));
        BaseType::wv.push_back(w);
        BaseType::l->addWidget(w,xi);
    }
}


QT_END_NAMESPACE

#endif
