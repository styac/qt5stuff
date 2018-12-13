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

#include "QyAbstractButton.h"
#include "QyAbstractButton_p.h"
#include "QyColors.h"

#include <qapplication.h>
#include "qevent.h"
#include "qdebug.h"
#ifndef QT_NO_ACCESSIBILITY
#include "qaccessible.h"
#endif
#include <limits.h>

QT_BEGIN_NAMESPACE

QyAbstractButtonPrivate::QyAbstractButtonPrivate()
    : id(0)
    , groupIndex(0)
    , stateOnColor(0,210,255,255)
    , stateOffColor(0,255,210,255)
{
}

QyAbstractButtonPrivate::~QyAbstractButtonPrivate()
{
}


//void QyAbstractButtonPrivate::recalculateStyleData( const QyAbstractButton * thp )
//{
//    QFontMetrics qFontMetrics(thp->font());
//    styleData.fontHeight = qFontMetrics.height();
//    const int captionHeight = styleData.caption.size() == 0 ? 0 : styleData.fontHeight + 4; // margin? ++ should even !
//    const int width = thp->rect().width();
//    const int height = thp->rect().height() - captionHeight;
//    const int minDimension = qMin(width, height);
//    int diffDimension = (width - height)/2;
//    if( captionHeight ) {
//        styleData.captionTextRect.setHeight(captionHeight);
//        styleData.captionTextRect.setWidth(width);
//        styleData.graphicsRect = thp->rect().adjusted(0,captionHeight,0,0);
//    } else {
//// not used
////        styleData.captionTextRect.setHeight(0);
////        styleData.captionTextRect.setWidth(0);
//        styleData.graphicsRect = thp->rect();
//    }
////    qDebug() << "recalculateStyleData  fontHeight: " << fontHeight ;

//    styleData.painterWidth = qMax( int(StyleData::minPainterWidth),
//        qMin( minDimension / StyleData::adjPainterWidth, int(StyleData::maxPainterWidth) ));

//    const int margin = (styleData.minMargin + styleData.painterWidth);

//    switch( styleData.graphicStyle ) {
//    case Qy::GSI_NoGraphics:
//        {
//            styleData.textBoxPlacement = Qy::TB_AutoTextBox;
//        }
//        break;
//    case Qy::GSI_Slider:
//        {

//        }
//        break;
//    case Qy::GSI_Rotary:
//        {
//            // handle orientation, mirroring,...
//            styleData.slotSize = 24*styleData.fracDegree;
//            styleData.arcBegin = 270*styleData.fracDegree - styleData.slotSize;
//            if( diffDimension > 0) {
//                styleData.graphicsRect.adjust(diffDimension + margin, margin, -diffDimension - margin, -margin);
//            } else {
//                styleData.graphicsRect.setBottom(minDimension);
//                styleData.graphicsRect.adjust(margin,margin,-margin,-margin);
//            }
//            styleData.valueTextRect = styleData.graphicsRect.adjusted( 0,0,0,0 );
//            // to test
//            styleData.sizeHint.setHeight(styleData.graphicsRect.height() + captionHeight);
//            styleData.sizeHint.setWidth(styleData.graphicsRect.width() );
//            // messageTextRect - one line under
//        }
//        break;
//    case Qy::GSI_HalfRotary:
//        {
//            // handle orientation, mirroring,...
//            styleData.slotSize = 90*styleData.fracDegree;
//            styleData.arcBegin = 180*styleData.fracDegree;
//            if( diffDimension > 0) {
//                // to test
//                styleData.sizeHint.setHeight(styleData.graphicsRect.height() + captionHeight);
//                styleData.sizeHint.setWidth(styleData.graphicsRect.width() );
//                int corr = height/2 - margin*2;
//                styleData.graphicsRect.adjust(diffDimension + margin -corr, margin, -diffDimension - margin + corr, - margin + corr*2);
//                styleData.valueTextRect = styleData.graphicsRect.adjusted( 0,0,0,-styleData.fontHeight );
//                // messageTextRect - one line under
//            } else {
//                styleData.graphicsRect.setBottom(minDimension);
//                styleData.graphicsRect.adjust(margin,margin,-margin,-margin);
//                styleData.valueTextRect = styleData.graphicsRect.adjusted( 0,0,0,-styleData.fontHeight/2 );
//                // to test
//                styleData.sizeHint.setHeight(styleData.graphicsRect.height() + captionHeight);
//                styleData.sizeHint.setWidth(styleData.graphicsRect.width() );
//                // messageTextRect - one line under
//            }
//        }
//        break;
//    case Qy::GSI_Triangle:
//        {

//        }
//        break;
//    case Qy::GSI_RoundLed:
//        {

//        }
//        break;
//    case Qy::GSI_SquareLed:
//        {

//        }
//        break;
//    default:
//        return;
//    }

//    switch( styleData.textBoxPlacement ) {
//    case Qy::TB_NoTextBox:
//        break;
//    case Qy::TB_AutoTextBox:


//        break;
//    case Qy::TB_TopTextBox:
//        break;
//    case Qy::TB_BottomTextBox:
//        break;
//    default:
//        return;
//    }
//}

QyAbstractButton::QyAbstractButton(QyAbstractButtonPrivate &dd, QWidget *parent)
    :QWidget(dd, parent, 0)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

QyAbstractButton::~QyAbstractButton()
{
}

void QyAbstractButton::setId( int val )
{
    Q_D(QyAbstractButton);
    d->id = val;
}

int QyAbstractButton::id() const
{
    Q_D(const QyAbstractButton);
    return d->id;
}

void QyAbstractButton::setGroupIndex( int val )
{
    Q_D(QyAbstractButton);
    d->groupIndex = val;
}

int QyAbstractButton::groupIndex() const
{
    Q_D(const QyAbstractButton);
    return d->groupIndex;
}


QString const& QyAbstractButton::text() const
{
    Q_D(const QyAbstractButton);
    return d->text;
}


void QyAbstractButton::setText(QString const& val)
{
    Q_D(QyAbstractButton);
    if( d->text == val ) {
        return;
    }
    d->text = val;
//    d->recalculateStyleData(this);
    update();
}


void QyAbstractButton::setStateOnColor(QColor const& val)
{
    Q_D(QyAbstractButton);
    if (d->stateOnColor == val)
        return;
    d->stateOnColor = val;
    update();
}

void QyAbstractButton::setStateOffColor(QColor const& val)
{
    Q_D(QyAbstractButton);
    if (d->stateOffColor == val)
        return;
    d->stateOffColor = val;
    update();
}

QColor const& QyAbstractButton::stateOnColor() const
{
    Q_D( const QyAbstractButton);
    return d->stateOnColor;
}

QColor const& QyAbstractButton::stateOffColor() const
{
    Q_D( const QyAbstractButton);
    return d->stateOffColor;
}

void QyAbstractButton::setChecked( bool val )
{
    Q_D(QyAbstractButton);
    if (d->state == val)
        return;
    d->state = val;
    update();
}

bool QyAbstractButton::checked() const
{
    Q_D(const QyAbstractButton);
    return d->state;
}

void QyAbstractButton::setToggleable( bool val )
{
    Q_D(QyAbstractButton);
    d->toggleable = val;
}

bool QyAbstractButton::toggleable() const
{
    Q_D(const QyAbstractButton);
    return d->toggleable;
}

void QyAbstractButton::setHoverable( bool val )
{
    Q_D(QyAbstractButton);
    d->hoverable = val;
}

bool QyAbstractButton::hoverable() const
{
    Q_D(const QyAbstractButton);
    return d->hoverable;
}

QT_END_NAMESPACE
