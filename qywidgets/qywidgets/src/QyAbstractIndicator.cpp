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

#include "QyAbstractIndicator.h"
#include "QyAbstractIndicator_p.h"
#include "QyColors.h"

#include <qapplication.h>
#include "qevent.h"
#include "qdebug.h"
#ifndef QT_NO_ACCESSIBILITY
#include "qaccessible.h"
#endif
#include <limits.h>

QT_BEGIN_NAMESPACE

QyAbstractIndicatorPrivate::QyAbstractIndicatorPrivate( bool res0 )
    : id(0)
    , groupIndex(0)
    , stateOnColor(0,255,210,255)
    , stateOffColor(0,210,255,255)
    , valueVector()
    , indicatorTransformer( valueVector, res0 )
{
}

QyAbstractIndicatorPrivate::~QyAbstractIndicatorPrivate()
{
}

#if 0

http://doc.qt.io/qt-5/layout.html


Custom Widgets in Layouts

When you make your own widget class, you should also communicate its layout properties.
If the widget uses one of Qt layouts, this is already taken care of.

If the widget does not have any child widgets, or uses manual layout,
you can change the behavior of the widget using any or all of the following mechanisms:


    Reimplement QWidget::sizeHint() to return the preferred size of the widget.
    Reimplement QWidget::minimumSizeHint() to return the smallest size the widget can have.
    Call QWidget::setSizePolicy() to specify the space requirements of the widget.

Call QWidget::updateGeometry() whenever the size hint, minimum size hint or size policy changes. This will cause a layout recalculation. Multiple consecutive calls to QWidget::updateGeometry() will only cause one layout recalculation.

If the preferred height of your widget depends on its actual width
(e.g., a label with automatic word-breaking), set the height-for-width flag in the widget size
policy and reimplement QWidget::heightForWidth().


Even if you implement QWidget::heightForWidth(), it is still a good idea to provide a reasonable sizeHint().

For further guidance when implementing these functions, see the Qt Quarterly article Trading Height for Width.
#endif


void QyAbstractIndicatorPrivate::recalculateStyleData( const QyAbstractIndicator * thp )
{
    QFontMetrics qFontMetrics(thp->font());
    styleData.fontHeight = qFontMetrics.height();
    const int captionHeight = styleData.caption.size() == 0 ? 0 : styleData.fontHeight + 4; // margin? ++ should even !
    const int width = thp->rect().width();
    const int height = thp->rect().height() - captionHeight;
    const int minDimension = qMin(width, height);
    int diffDimension = (width - height)/2;
    if( captionHeight ) {
        styleData.captionTextRect.setHeight(captionHeight);
        styleData.captionTextRect.setWidth(width);
        styleData.graphicsRect = thp->rect().adjusted(0,captionHeight,0,0);
    } else {
// not used
//        styleData.captionTextRect.setHeight(0);
//        styleData.captionTextRect.setWidth(0);
        styleData.graphicsRect = thp->rect();
    }
//    qDebug() << "recalculateStyleData  fontHeight: " << fontHeight ;

    styleData.painterWidth = qMax( int(StyleDataIndicator::minPainterWidth),
        qMin( minDimension / StyleDataIndicator::adjPainterWidth, int(StyleDataIndicator::maxPainterWidth) ));

    const int margin = (styleData.minMargin + styleData.painterWidth);

    switch( styleData.graphicStyle ) {
    case Qy::GSI_NoGraphics:
        {
            styleData.textBoxPlacement = Qy::TB_AutoTextBox;
        }
        break;
    case Qy::GSI_Slider:
        {

        }
        break;
    case Qy::GSI_Rotary:
        {
            // handle orientation, mirroring,...
            styleData.slotSize = 24*styleData.fracDegree;
            styleData.arcBegin = 270*styleData.fracDegree - styleData.slotSize;
            if( diffDimension > 0) {
                styleData.graphicsRect.adjust(diffDimension + margin, margin, -diffDimension - margin, -margin);
            } else {
                styleData.graphicsRect.setBottom(minDimension);
                styleData.graphicsRect.adjust(margin,margin,-margin,-margin);
            }
            styleData.valueTextRect = styleData.graphicsRect.adjusted( 0,0,0,0 );
            // to test
            styleData.sizeHint.setHeight(styleData.graphicsRect.height() + captionHeight);
            styleData.sizeHint.setWidth(styleData.graphicsRect.width() );
            // messageTextRect - one line under
        }
        break;
    case Qy::GSI_HalfRotary:
        {
            // handle orientation, mirroring,...
            styleData.slotSize = 90*styleData.fracDegree;
            styleData.arcBegin = 180*styleData.fracDegree;
            if( diffDimension > 0) {
                // to test
                styleData.sizeHint.setHeight(styleData.graphicsRect.height() + captionHeight);
                styleData.sizeHint.setWidth(styleData.graphicsRect.width() );
                int corr = height/2 - margin*2;
                styleData.graphicsRect.adjust(diffDimension + margin -corr, margin, -diffDimension - margin + corr, - margin + corr*2);
                styleData.valueTextRect = styleData.graphicsRect.adjusted( 0,0,0,-styleData.fontHeight );
                // messageTextRect - one line under
            } else {
                styleData.graphicsRect.setBottom(minDimension);
                styleData.graphicsRect.adjust(margin,margin,-margin,-margin);
                styleData.valueTextRect = styleData.graphicsRect.adjusted( 0,0,0,-styleData.fontHeight/2 );
                // to test
                styleData.sizeHint.setHeight(styleData.graphicsRect.height() + captionHeight);
                styleData.sizeHint.setWidth(styleData.graphicsRect.width() );
                // messageTextRect - one line under
            }
        }
        break;
    case Qy::GSI_Triangle:
        {

        }
        break;
    case Qy::GSI_RoundLed:
        {

        }
        break;
    case Qy::GSI_SquareLed:
        {

        }
        break;
    default:
        return;
    }

    switch( styleData.textBoxPlacement ) {
    case Qy::TB_NoTextBox:
        break;
    case Qy::TB_AutoTextBox:


        break;
    case Qy::TB_TopTextBox:
        break;
    case Qy::TB_BottomTextBox:
        break;
    default:
        return;
    }
}

QyAbstractIndicator::QyAbstractIndicator(QyAbstractIndicatorPrivate &dd, QWidget *parent)
    :QFrame(dd, parent, 0)
{
    setSymmetric(false);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QyBase::Rainbow::getInstance().set0( this->palette().color(QWidget::backgroundRole()) );
}

QyAbstractIndicator::~QyAbstractIndicator()
{
}

void QyAbstractIndicator::setId( int val )
{
    Q_D(QyAbstractIndicator);
    d->id = val;
}

int QyAbstractIndicator::id() const
{
    Q_D(const QyAbstractIndicator);
    return d->id;
}


QString const& QyAbstractIndicator::caption() const
{
    Q_D(const QyAbstractIndicator);
    return d->styleData.caption;
}

QString const& QyAbstractIndicator::suffix(uint8_t index) const
{
    Q_D(const QyAbstractIndicator);
    return d->valueVector.getSuffix(index);
}

void QyAbstractIndicator::setCaption(QString const& val)
{
    Q_D(QyAbstractIndicator);
    if( d->styleData.caption == val ) {
        return;
    }
    d->styleData.caption = val;
    d->recalculateStyleData(this);
    update();
}

void QyAbstractIndicator::setSuffix(QString const& val, uint8_t index )
{
    Q_D(QyAbstractIndicator);
    if( ! d->valueVector.setSuffix(val, index) ) {
        return;
    }
    d->recalculateStyleData(this);
    update();
}

// TODO
void QyAbstractIndicator::setRange(double min, double max)
{
    Q_D(QyAbstractIndicator);
    if( d->indicatorTransformer.setRange(min, max) ) {
        // update value
        // update
    }
}

void QyAbstractIndicator::setMinimum(double min)
{
    Q_D(QyAbstractIndicator);
    setRange(min, d->indicatorTransformer.getMaximum());
}

double QyAbstractIndicator::minimum() const
{
    Q_D(const QyAbstractIndicator);
    return d->indicatorTransformer.getMinimum();
}

void QyAbstractIndicator::setMaximum(double max)
{
    Q_D(QyAbstractIndicator);
    setRange(d->indicatorTransformer.getMinimum(), max);
}

double QyAbstractIndicator::maximum() const
{
    Q_D(const QyAbstractIndicator);
    return d->indicatorTransformer.getMaximum();
}

void QyAbstractIndicator::setSymmetric( bool val )
{
    Q_D(QyAbstractIndicator);
    if( d->indicatorTransformer.setSymmetric(val) ) {
        update();
    }
}

bool QyAbstractIndicator::symmetric() const
{
    Q_D(const QyAbstractIndicator);
    return d->indicatorTransformer.getSymmetric();
}

double QyAbstractIndicator::value(int index) const
{
    Q_D(const QyAbstractIndicator);
    return d->indicatorTransformer.getValue( d->styleData.controllerIndicator ? 1 : 0 );
}

void QyAbstractIndicator::setValue(double val, int index)
{
    Q_D(QyAbstractIndicator);
    if( d->indicatorTransformer.setValue( val, d->styleData.controllerIndicator ? 1 : 0 )) {
        update();
    }
}

void QyAbstractIndicator::initTransformParameters( double p0, double p1 )
{
    Q_D(QyAbstractIndicator);
    d->indicatorTransformer.initTransformParameters(p0,p1);
}

bool QyAbstractIndicator::registerTransformFunctions( QyBase::TransfomerParameters::FpSlider2value slider2value, QyBase::TransfomerParameters::FpValue2slider value2slider, QyBase::TransfomerParameters::FpSetMinMax setValueRange )
{
    Q_D(QyAbstractIndicator);
    return d->indicatorTransformer.registerTransformFunctions(slider2value, value2slider, setValueRange);
}

void QyAbstractIndicator::setMirrored ( bool val )
{
    Q_D(QyAbstractIndicator);
    if( d->styleData.mirrored == val ) {
        return;
    }
    d->styleData.mirrored = val;
    d->recalculateStyleData(this);
    update();
}

void QyAbstractIndicator::setInvertedFlow ( bool val )
{
    Q_D(QyAbstractIndicator);
    if( d->styleData.invertedFlow == val ) {
        return;
    }
    d->styleData.invertedFlow = val;
    d->recalculateStyleData(this);
    update();
}

void QyAbstractIndicator::setOrientation(Qt::Orientation val )
{
    Q_D(QyAbstractIndicator);
    if (d->styleData.orientation == val)
        return;
    d->styleData.orientation = val;
    d->recalculateStyleData(this);
    update();
}

void QyAbstractIndicator::setGraphicStyle(Qy::GraphicStyleIndicator val)
{
    Q_D(QyAbstractIndicator);
    if( val >= Qy::GSI_MAX) {
        return;
    }
    if( val == d->styleData.graphicStyle ) {
        return;
    }
    d->styleData.graphicStyle = val;
    d->recalculateStyleData(this);

    // setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    update();
}

void QyAbstractIndicator::setColorStyle(Qy::ColorStyle val)
{
    Q_D(QyAbstractIndicator);
    if( val >= Qy::CS_MAX) {
        return;
    }
    if( val == d->styleData.colorStyle ) {
        return;
    }
    d->styleData.colorStyle = val;
    update();
}

void QyAbstractIndicator::setTextBoxPlacement(Qy::TextBoxPlacement val)
{
    Q_D(QyAbstractIndicator);
    if( val >= Qy::TB_MAX) {
        return;
    }
    if( val == d->styleData.textBoxPlacement ) {
        return;
    }
    d->styleData.textBoxPlacement = val;
    d->recalculateStyleData(this);
    update();
}

void QyAbstractIndicator::setSequenceOrientation(Qt::Orientation val )
{
    Q_D(QyAbstractIndicator);
    if (d->styleData.sequenceOrientation == val)
        return;
    d->styleData.sequenceOrientation = val;
    update();
}

Qt::Orientation QyAbstractIndicator::sequenceOrientation() const
{
    Q_D(const QyAbstractIndicator);
    return d->styleData.sequenceOrientation;
}

Qt::Orientation QyAbstractIndicator::orientation() const
{
    Q_D(const QyAbstractIndicator);
    return d->styleData.orientation;
}

Qy::GraphicStyleIndicator QyAbstractIndicator::graphicStyle() const
{
    Q_D(const QyAbstractIndicator);
    return d->styleData.graphicStyle;
}

Qy::TextBoxPlacement QyAbstractIndicator::textBoxPlacement() const
{
    Q_D(const QyAbstractIndicator);
    return d->styleData.textBoxPlacement;
}

Qy::ColorStyle QyAbstractIndicator::colorStyle() const
{
    Q_D(const QyAbstractIndicator);
    return d->styleData.colorStyle;
}

bool QyAbstractIndicator::mirrored() const
{
    Q_D( const QyAbstractIndicator);
    return d->styleData.mirrored;
}

bool QyAbstractIndicator::invertedFlow() const
{
    Q_D( const QyAbstractIndicator);
    return d->styleData.invertedFlow;
}

void QyAbstractIndicator::setTextColor(QColor const& val)
{
    Q_D(QyAbstractIndicator);
    if (d->styleData.textColor == val)
        return;
    d->styleData.textColor = val;
    update();
}

void QyAbstractIndicator::setStateOffColor(QColor const& val)
{
    Q_D(QyAbstractIndicator);
    if (d->styleData.stateOffColor == val)
        return;
    d->styleData.stateOffColor = val;
    update();
}

void QyAbstractIndicator::setStateOnColor(QColor const& val)
{
    Q_D(QyAbstractIndicator);
    if (d->styleData.stateOnColor == val)
        return;
    d->styleData.stateOnColor = val;
    update();
}

QColor const& QyAbstractIndicator::textColor() const
{
    Q_D( const QyAbstractIndicator);
    return d->styleData.textColor;
}

QColor const& QyAbstractIndicator::stateOffColor() const
{
    Q_D( const QyAbstractIndicator);
    return d->styleData.stateOffColor;
}

QColor const& QyAbstractIndicator::stateOnColor() const
{
    Q_D( const QyAbstractIndicator);
    return d->styleData.stateOnColor;
}

//void QyAbstractIndicator::setGroupIndex( int val )
//{
//    Q_D(QyAbstractIndicator);
//    d->groupIndex = val;
//}

int QyAbstractIndicator::groupIndex() const
{
    Q_D(const QyAbstractIndicator);
    return d->groupIndex;
}

QT_END_NAMESPACE
