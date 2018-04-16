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


#include "QyStyleOption.h"

#include <qapplication.h>
#include <qbitmap.h>
#include <qcolor.h>
#include <qevent.h>
#include <qpainter.h>
#include <qpolygon.h>
#include <qregion.h>
#include <qstyle.h>
#include <qstylepainter.h>
#include <qstyleoption.h>
#include <private/qmath_p.h>
#ifndef QT_NO_ACCESSIBILITY
#include "qaccessible.h"
#endif
#include <qmath.h>

#include <qpainter.h>
#include <qpixmapcache.h>
#include <private/qmath_p.h>
#include <private/qstyle_p.h>

#if 0
resize

class FontAdjustingButton : public QPushButton {
public:
  explicit FontAdjustingButton(QWidget *parent = NULL) : QPushButton(parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  }
protected:
  void resizeEvent(QResizeEvent *event) {
    int button_margin = style()->pixelMetric(QStyle::PM_ButtonMargin);
    QFont f = font();
    f.setPixelSize(event->size().height() - button_margin * 2);
    setFont(f);
  }
};
#endif

QT_BEGIN_NAMESPACE

void drawQyMinimalStyle( const QyStyleOption *opt, QPainter *p )
{
    constexpr int fracDegree = 16;     // 5760 (16 * 360).
    constexpr int circleFracDegree = fracDegree * 360;
    constexpr int maxPainterWidth = 8;
    constexpr int minPainterWidth = 2;
    constexpr int adjPainterWidth = 30;
    constexpr int minSizeForText = 20; // TODO test
    const auto palette = opt->palette;
    const auto width = opt->rect.width();
    const auto height = opt->rect.height();
    QColor leftColor(opt->styleData->leftColor);
    QColor rightColor(opt->styleData->rightColor);

    if( !(opt->state & QStyle::State_Enabled) ) {
        leftColor.setAlpha( opt->styleData->disableStateColorAlpha );
        rightColor.setAlpha( opt->styleData->disableStateColorAlpha );
    } else if( opt->styleData->remoteControlled ) {
        leftColor.setAlpha( opt->styleData->remoteStateColorAlpha );
        rightColor.setAlpha( opt->styleData->remoteStateColorAlpha );
    }

    const int squareSize = qMin(width, height);
    const int painterWidth = qMax( minPainterWidth, qMin( squareSize / adjPainterWidth, maxPainterWidth ));
    const int borderDisterDisterDist = painterWidth+5;

    const auto& textRect = opt->styleData->valueTextRect;
    auto textBoxPlacement = opt->styleData->textBoxPlacement;

    if( width < minSizeForText) {   // TODO test -- ?
        textBoxPlacement = Qy::TB_NoTextBox;
    }

    p->save();
    QPen text( opt->styleData->textColor );
    if( opt->styleData->caption.size() ) {
        int textAlign = Qt::AlignHCenter | Qt::AlignVCenter;
        p->setPen(text);
        p->drawText(opt->styleData->captionTextRect,textAlign,opt->styleData->caption);
    }

    switch( opt->styleData->graphicStyle ) {
    case Qy::GS_NoGraphics:
        break;
// ----------------------------
    case Qy::GS_Rotary:
        {
            const int slotSize = opt->styleData->slotSize;
            const int arcBegin = opt->styleData->arcBegin;
            QRect rect( opt->styleData->graphicsRect );
            int fullArc = circleFracDegree - 2*slotSize; //opt->slotSize; -- not needed
            int valDeg = -opt->valueDisplay->getPaintValue(fullArc,0);
            p->setRenderHint(QPainter::Antialiasing);
            QPen leftPen( leftColor );
            leftPen.setWidth(painterWidth);
            QPen rightPen( rightColor );
            rightPen.setWidth(painterWidth);

            p->setPen( rightPen );
            p->drawArc(rect, arcBegin+valDeg, -fullArc-valDeg);
            p->setPen( leftPen );
            p->drawArc(rect, arcBegin, valDeg);

            if( textBoxPlacement == Qy::TB_NoTextBox ) {
                 p->restore();
                 return;
            }
        }
        break;

// ----------------------------
    case Qy::GS_HalfRotary:
        {
            const int slotSize = opt->styleData->slotSize;
            const int arcBegin = opt->styleData->arcBegin;
            QRect rect( opt->styleData->graphicsRect );
            int fullArc = circleFracDegree - 2*slotSize; //opt->slotSize; -- not needed
            int valDeg = -opt->valueDisplay->getPaintValue(fullArc,0);
            p->setRenderHint(QPainter::Antialiasing);
            QPen leftPen( leftColor );
            leftPen.setWidth(painterWidth);
            QPen rightPen( rightColor );
            rightPen.setWidth(painterWidth);

            p->setPen( rightPen );
            p->drawArc(rect, arcBegin+valDeg, -fullArc-valDeg);
            p->setPen( leftPen );
            p->drawArc(rect, arcBegin, valDeg);

            if( textBoxPlacement == Qy::TB_NoTextBox ) {
                 p->restore();
                 return;
            }
        }
        break;
// ----------------------------
//    case QyStyleOptionController::GS_Slider:
//        {
        //  QPainter::drawLine(int x1, int y1, int x2, int y2)
//        }
//        return;

    default:
        p->restore();
        return;
    }
    int textAlign = Qt::AlignHCenter | Qt::AlignVCenter;
    p->setPen(text);
    p->drawText(textRect,textAlign,opt->valueDisplay->getValueString(0)); //
    p->restore();
}

QT_END_NAMESPACE
