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
#include <QDebug>

QT_BEGIN_NAMESPACE

typedef QVector<QString> StringVectorType;

template< class WidgetType, class LayoutType >
class QyWidgetVector {
public:
    using WidgetVector = QVector<WidgetType *>;
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
        thisSize = wv[0]->size();
        int margin = 12; // TODO get margin
        thisSize.setHeight( row * thisSize.height() + margin + colLabelHeight );
        thisSize.setWidth(( col > 0 ? col : 1 ) * thisSize.width() + margin + rowLabelWidth );
        return thisSize;
    }

    inline const QSize& size() const
    {
        return thisSize;
    }

    inline void applyId( int id, bool rowSequence = true )
    {
        if( rowSequence || (col==0) ) {
            for( auto& v : wv ) {

//                // TEST BEGIN
//                QString cap( QString("%0").arg(idv) );
//                v->setCaption( cap );
//                // TEST END
                v->setId(id++);
            }
            return;
        }
        // TODO make coloumn sequence
        for( auto& v : wv ) {
            v->setId(id++);
        }
    }

    //  apply captions
    //  apply suffix
    //  ...

protected:
    QyWidgetVector() = delete;
    QyWidgetVector( uint16_t rowp, uint16_t colp )
    : wv()
    , l()
    , thisSize()
    , colLabelHeight(0)
    , rowLabelWidth(0)
    , row(rowp==0 ? 1 : rowp) // x cannot be 0
    , col(colp)   // if y is zero then it is not grid
    , flags(0)
    {}

    WidgetVector            wv;
    LayoutType            * l;
    QSize                   thisSize;
    int                     colLabelHeight;
    int                     rowLabelWidth;
    const uint16_t          row;
    const uint16_t          col;
    union {
        uint16_t            flags;
        struct {
            uint16_t useRowLabels : 1;
            uint16_t useColLabels : 1;
        };
    };
};

template< class WidgetType >
class QyWidgetVectorGrid : public QyWidgetVector<WidgetType, QGridLayout> {
public:
    using LayoutType = QGridLayout;
    using BaseType = QyWidgetVector<WidgetType, LayoutType>;
    QyWidgetVectorGrid() = delete;
    QyWidgetVectorGrid( uint16_t rowp, uint16_t colp, bool colMajor, const QString& objectNameBase,
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
                    auto * w = new WidgetType(obni);
                    w->setObjectName(QString("%0_%1").arg( objectNameBase ).arg(obni));
                    // setAccessibleName(const QString &name)
                    BaseType::wv.push_back(w);
                    BaseType::l->addWidget(w,row,col);
                }
            }
        } else {
            for( uint16_t row = row0; row < rowp; ++row ) {
                for( uint16_t col = col0; col < colp; ++col, ++obni ) {
                    auto * w = new WidgetType(obni);
                    w->setObjectName(QString("%0_%1").arg( objectNameBase ).arg(obni));
                    // setAccessibleName(const QString &name)
                    BaseType::wv.push_back(w);
                    BaseType::l->addWidget(w,row,col);
                }
            }
        }
    }
};

// TODO adapt changes - add labels
template< class WidgetType >
class QyWidgetVectorBox : public QyWidgetVector<WidgetType, QBoxLayout> {
public:
    using LayoutType = QBoxLayout;
    using BaseType = QyWidgetVector<WidgetType, LayoutType>;
    QyWidgetVectorBox() = delete;
    QyWidgetVectorBox( uint16_t rowp, LayoutType::Direction direction,
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
            WidgetType * w = new WidgetType(xi);
            w->setObjectName(QString("%0_%1").arg( objectNameBase ).arg(xi));
            BaseType::wv.push_back(w);
            BaseType::l->addWidget(w,xi);
        }
    }
};


QT_END_NAMESPACE
