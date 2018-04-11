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
    : valueVector()
    , indicatorTransformer( valueVector, res0 )
    , leftColor(0,255,210,255)
    , rightColor(0,210,255,255)
{
}

QyAbstractIndicatorPrivate::~QyAbstractIndicatorPrivate()
{
}

void QyAbstractIndicatorPrivate::recalculateStyleData( const QyAbstractIndicator * thp )
{
    qDebug() << "recalculateStyleData ";
    const int minDimension = qMin(thp->rect().width(), thp->rect().height());
    const int diffDimension = thp->rect().width() - thp->rect().height();

    styleData.painterWidth = qMax( int(StyleData::minPainterWidth),
        qMin( minDimension / StyleData::adjPainterWidth, int(StyleData::maxPainterWidth) ));

    const int margin = (styleData.minMargin + styleData.painterWidth);
    styleData.graphicsRect = thp->rect();

    switch( styleData.graphicStyle ) {
    case Qy::GS_NoGraphics:
        {
            styleData.textBoxPlacement = Qy::TB_AutoTextBox;
        }
        break;
    case Qy::GS_Slider:
        {

        }
        break;
    case Qy::GS_Gauge:
        {
            if( diffDimension > 0) {
                styleData.graphicsRect.adjust(diffDimension/2+margin, margin, -diffDimension/2-margin,-margin);
            } else {
                styleData.graphicsRect.setBottom(minDimension);
                styleData.graphicsRect.adjust(margin,margin,-margin,-margin);
            }
            styleData.valueTextRect = styleData.graphicsRect.adjusted(0,0,0,0 );
            // infoTextRect - one line under
        }
        break;
    case Qy::GS_HalfGauge:
        {

        }
        break;
    case Qy::GS_Triangle:
        {

        }
        break;
    case Qy::GS_RoundLed:
        {

        }
        break;
    case Qy::GS_SquareLed:
        {

        }
        break;
//    case Qy::GS_TwinSlider:
//        {

//        }
//        break;
//    case Qy::GS_TwinHalfGauge:
//        {

//        }
//        break;
//    case Qy::GS_ConcentricGauge:
//        {

//        }
//        break;
//    case Qy::GS_ConcentricHalfGauge:
//        {

//        }
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

//QyAbstractIndicator::QyAbstractIndicator(QWidget *parent)
//    :QFrame(*new QyAbstractIndicatorPrivate, parent, 0)
//{
//    QyBase::Rainbow::getInstance().set0( this->palette().color(QWidget::backgroundRole()) );
//}

QyAbstractIndicator::QyAbstractIndicator(QyAbstractIndicatorPrivate &dd, QWidget *parent)
    :QFrame(dd, parent, 0)
{
    qDebug() << "--ctor--  QyAbstractIndicator-dd";
    setSymmetric(false);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QyBase::Rainbow::getInstance().set0( this->palette().color(QWidget::backgroundRole()) );
}

QyAbstractIndicator::~QyAbstractIndicator()
{
}


QString const& QyAbstractIndicator::title() const
{
    Q_D(const QyAbstractIndicator);
    return d->title;
}


void QyAbstractIndicator::setTitle(QString const& val)
{
    Q_D(QyAbstractIndicator);
    d->title = val;
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
    constexpr int alphaEnabled = 255;
    Q_D(QyAbstractIndicator);
    if( d->indicatorTransformer.setSymmetric(val) ) {
        d->styleData.setColors( d->leftColor
            , val ? d->rightColor : this->palette().color(QPalette::Window).darker()
            , alphaEnabled
            , alphaEnabled );
        update();
    }
}

bool QyAbstractIndicator::symmetric() const
{
    Q_D(const QyAbstractIndicator);
    return d->indicatorTransformer.getSymmetric();
}

//QyBase::ValueIO QyAbstractIndicator::value() const
//{
//    Q_D(const QyAbstractIndicator);
//    return d->indicatorTransformer.getValue();
//}

//void QyAbstractIndicator::setValue(const QyBase::ValueIO& value)
//{
//    Q_D(QyAbstractIndicator);
//    if( d->indicatorTransformer.setValue( value )) {
//        update();
//    }
//}

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

//ValueType QyAbstractIndicator::valueVector() const
//{
//    Q_D(const QyAbstractIndicator);
//    ValueType vv;
//    // get the pairs from ValueVector
//    return vv;
//}
//void QyAbstractIndicator::setValueVector(const ValueType&)
//{
//    Q_D(QyAbstractIndicator);
//    // set the pairs to ValueVector
//}


void QyAbstractIndicator::setMirrored ( bool val )
{
    Q_D(QyAbstractIndicator);
    d->styleData.mirrored = val;
    d->recalculateStyleData(this);
    update();
}

void QyAbstractIndicator::setInvertedFlow ( bool val )
{
    Q_D(QyAbstractIndicator);
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

void QyAbstractIndicator::setGraphicStyle(Qy::GraphicStyle val)
{
    Q_D(QyAbstractIndicator);
    if( val >= Qy::GS_MAX) {
        return;
    }
    if( val == d->styleData.graphicStyle ) {
        return;
    }
    d->styleData.graphicStyle = val;
    d->recalculateStyleData(this);
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

Qy::GraphicStyle QyAbstractIndicator::graphicStyle() const
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

QT_END_NAMESPACE
