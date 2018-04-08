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

#include <qapplication.h>
#include "qevent.h"
#include "QyAbstractController_p.h"

#include "qdebug.h"
#ifndef QT_NO_ACCESSIBILITY
#include "qaccessible.h"
#endif
#include <limits.h>

QT_BEGIN_NAMESPACE

QyAbstractControllerPrivate::QyAbstractControllerPrivate()
    : QyAbstractIndicatorPrivate( true ) // vv[0] reserved
    , valueHandler()
    , controllerTransformer( valueVector, true ) // vv[0] reserved
    , lastPosition(0)
    , userEventValue(0)
    , flags(0)
{
    qDebug() << "--ctor--  QyAbstractControllerPrivate";
}

QyAbstractControllerPrivate::~QyAbstractControllerPrivate()
{
}

bool QyAbstractControllerPrivate::valueFromPoint(int disp)
{
    constexpr int giantStepping = 12;

    Q_Q(const QyAbstractController);
    int tt = lastPosition;
    int dposition = disp - lastPosition;
//    qDebug() << "disp " << disp << " last " << lastPosition << " delta " << dposition << " start pos " << tt;
    if( 0 == dposition ) {
        return false;
    }
    lastPosition = disp;
    int ab = qAbs(dposition);
    int sign = dposition > 0 ? 1 : -1;
    switch(ab) {
    case 1:
        return controllerTransformer.addSliderValue(valueHandler.getStepValue(QyBase::STEPS::STEP_TINY) * sign, 0);
    case 2:
        return controllerTransformer.addSliderValue(valueHandler.getStepValue(QyBase::STEPS::STEP_TINY_PLUS) * sign, 0);
    case 3:
        return controllerTransformer.addSliderValue(valueHandler.getStepValue(QyBase::STEPS::STEP_SINGLE) * sign, 0);
    case 4:
        return controllerTransformer.addSliderValue(valueHandler.getStepValue(QyBase::STEPS::STEP_SINGLE_PLUS) * sign, 0);
    }
    if( ab >= giantStepping ) {
        return controllerTransformer.stepGiant( sign * valueHandler.getStepValue(QyBase::STEPS::STEP_PAGE) );
    }
    return controllerTransformer.addSliderValue(valueHandler.getStepValue(QyBase::STEPS::STEP_PAGE) * sign, 0);
}

void QyAbstractControllerPrivate::setSteps(int single, int page)
{
    Q_Q(QyAbstractController);
    valueHandler.setPageStep(page);
    valueHandler.setSingleStep(single);
}


//QyAbstractController::QyAbstractController(QWidget *parent)
//    : QyAbstractIndicator(*new QyAbstractIndicatorPrivate, parent)
//{
//    qDebug() << "--ctor--  QyAbstractIndicator-new";
//}

QyAbstractController::QyAbstractController(QyAbstractControllerPrivate &dd, QWidget *parent)
    : QyAbstractIndicator(dd, parent)
{
    qDebug() << "--ctor--  QyAbstractIndicator-dd";
    setSymmetric(false);
}

QyAbstractController::~QyAbstractController()
{
}

void QyAbstractController::setRange(double min, double max)
{
    Q_D(QyAbstractController);
    if( d->controllerTransformer.setRange(min, max) ) {
        emit rangeChanged(d->controllerTransformer.getMinimum(), d->controllerTransformer.getMaximum());
        if( d->controllerTransformer.recalculate(0) ) {
            emit valueChanged( d->controllerTransformer.getValue(0) );
            update();
        }
    }
}

void QyAbstractController::setMinimum(double val)
{
    Q_D(QyAbstractController);
    if( d->controllerTransformer.setMinimum(val) ) {
        emit rangeChanged(d->controllerTransformer.getMinimum(), d->controllerTransformer.getMaximum());
    }
}

double QyAbstractController::minimum() const
{
    Q_D(const QyAbstractController);
    return d->controllerTransformer.getMinimum();
}

void QyAbstractController::setMaximum(double val)
{
    Q_D(QyAbstractController);
    if( d->controllerTransformer.setMaximum(val) ) {
        emit rangeChanged(d->controllerTransformer.getMinimum(), d->controllerTransformer.getMaximum());
    }
}

double QyAbstractController::maximum() const
{
    Q_D(const QyAbstractController);
    return d->controllerTransformer.getMaximum();
}

void QyAbstractController::setSingleStep(int step)
{
    Q_D(QyAbstractController);
    d->valueHandler.setSingleStep(step);
}

int QyAbstractController::singleStep() const
{
    Q_D(const QyAbstractController);
    return d->valueHandler.getSingleStep();
}

void QyAbstractController::setPageStep(int step)
{
    Q_D(QyAbstractController);
    d->valueHandler.setPageStep(step);
}

int QyAbstractController::pageStep() const
{
    Q_D(const QyAbstractController);
    return d->valueHandler.getPageStep();
}

void QyAbstractController::setUserEventValue(int val)
{
    Q_D(QyAbstractController);
    d->userEventValue = val;
}

int QyAbstractController::userEventValue() const
{
    Q_D(const QyAbstractController);
    return d->userEventValue;
}

void QyAbstractController::setSymmetric( bool val )
{
    constexpr int alphaEnabled = 255;
    constexpr int alphaDisabled = 64;
    Q_D(QyAbstractController);
    if( d->controllerTransformer.setSymmetric(val) ) {
        d->styleData.setColors( d->leftColor
            , val ? d->rightColor : this->palette().color(QPalette::Window).darker()
            , alphaEnabled
            , alphaDisabled );
        d->controllerTransformer.reset(0);
        update();
    }
}

void QyAbstractController::setControllerIndicator(bool val)
{
    Q_D(QyAbstractController);
    if( d->styleData.controllerIndicator != val ) {
        d->styleData.controllerIndicator = val;
        if( val ) {
            d->valueVector.setSize(2);
        }
    }
}

bool QyAbstractController::symmetric() const
{
    Q_D(const QyAbstractController);
    return d->controllerTransformer.getSymmetric();
}

bool QyAbstractController::controllerIndicator() const
{
    Q_D(const QyAbstractController);
    return d->styleData.controllerIndicator;
}

double QyAbstractController::value() const
{
    Q_D(const QyAbstractController);
    return d->controllerTransformer.getValue(0);
}

void QyAbstractController::setValue(double value)
{
    Q_D(QyAbstractController);
    if( d->controllerTransformer.setValue( value, 0 )) {
        update();
        emit valueChanged( value );
        if( d->emitSliderValue ) {
            const auto sliderValue = d->controllerTransformer.getSliderValue(0);
            emit sliderPositionChanged( sliderValue ? QyBase::maximumSlider - sliderValue : sliderValue );
        }
    }
}

//void QyAbstractController::wheelEvent(QWheelEvent * e)
//{
//    Q_D(QyAbstractController);
//    e->ignore();
//    int delta = e->delta();
//    // TODO something
//}

int QyAbstractController::sliderMaximum() const
{
    return QyBase::maximumSlider;
}

int QyAbstractController::sliderMinimum() const
{
    return QyBase::minimumSlider;
}

int QyAbstractController::sliderPosition() const
{
    Q_D( const QyAbstractController);
    return d->controllerTransformer.getSliderValue(0);
}

void QyAbstractController::setSliderPosition(int val)
{
    Q_D(QyAbstractController);
    if( d->controllerTransformer.setSliderValue(val,0) ) {
        if( d->emitSliderValue ) {
            const auto invert = d->invertSliderValue;
            emit sliderPositionChanged( invert ? QyBase::maximumSlider - val : val );
        }
        update();
    }
}

bool QyAbstractController::emitSliderValue() const
{
    Q_D( const QyAbstractController);
    return d->emitSliderValue;
}

bool QyAbstractController::invertSliderValue() const
{
    Q_D( const QyAbstractController);
    return d->invertSliderValue;
}

void QyAbstractController::setEmitSliderValue(bool val)
{
    Q_D(QyAbstractController);
    if( d->emitSliderValue != val ) {
        d->emitSliderValue = val;
        if( val ) {
            const auto invert = d->invertSliderValue;
            const auto sliderValue = d->controllerTransformer.getSliderValue(0);
            emit sliderPositionChanged( invert ? QyBase::maximumSlider - sliderValue : sliderValue );
        }
    }
}

void QyAbstractController::setInvertSliderValue(bool val)
{
    Q_D(QyAbstractController);
    if( d->invertSliderValue != val ) {
        d->invertSliderValue = val;
        if( d->emitSliderValue ) {
            const auto sliderValue = d->controllerTransformer.getSliderValue(0);
            emit sliderPositionChanged( val ? QyBase::maximumSlider - sliderValue : sliderValue );
        }
    }
}


// why is  keyPressEvent here ? and mouse in QyController

//void QyAbstractController::keyPressEvent(QKeyEvent *ev)
//{
//    Q_D(QyAbstractController);
//    int32_t stepValue = 0;
//    if( ev->modifiers() & Qt::ShiftModifier ) {
//        switch (ev->key()) {
//        case Qt::Key_Down:
//            stepValue = - d->valueHandler.getStepValue(QyBase::STEPS::STEP_SINGLE_PLUS);
//            break;
//        case Qt::Key_Left:
//            stepValue = - d->valueHandler.getStepValue(QyBase::STEPS::STEP_TINY_PLUS);
//            break;
//        case Qt::Key_Up:
//            stepValue = d->valueHandler.getStepValue(QyBase::STEPS::STEP_SINGLE_PLUS);
//            break;
//        case Qt::Key_Right:
//            stepValue = d->valueHandler.getStepValue(QyBase::STEPS::STEP_TINY_PLUS);
//            break;
//        case Qt::Key_PageUp:
//            d->controllerTransformer.stepGiant( d->valueHandler.getStepValue(QyBase::STEPS::STEP_PAGE));
//            break;
//        case Qt::Key_PageDown:
//            d->controllerTransformer.stepGiant( -d->valueHandler.getStepValue(QyBase::STEPS::STEP_PAGE));
//            break;
//        case Qt::Key_Home:
//            d->controllerTransformer.reset();
//            break;
//        case Qt::Key_End:
//            break;
//        default:
//            ev->ignore();
//            return;
//        }
//    } else {
//        switch (ev->key()) {
//        case Qt::Key_Down:
//            stepValue = - d->valueHandler.getStepValue(QyBase::STEPS::STEP_SINGLE);
//            break;
//        case Qt::Key_Left:
//            stepValue = - d->valueHandler.getStepValue(QyBase::STEPS::STEP_TINY);
//            break;
//        case Qt::Key_Up:
//            stepValue = d->valueHandler.getStepValue(QyBase::STEPS::STEP_SINGLE);
//            break;
//        case Qt::Key_Right:
//            stepValue = d->valueHandler.getStepValue(QyBase::STEPS::STEP_TINY);
//            break;
//        case Qt::Key_PageUp:
//            stepValue = d->valueHandler.getStepValue(QyBase::STEPS::STEP_PAGE);
//            break;
//        case Qt::Key_PageDown:
//            stepValue = - d->valueHandler.getStepValue(QyBase::STEPS::STEP_PAGE);
//            break;
//        case Qt::Key_Home:
//            d->controllerTransformer.reset();
//            break;
//        case Qt::Key_End:
//            break;
//        default:
//            ev->ignore();
//            return;
//        }
//    }
//    if( stepValue ) {
//        if( ! d->controllerTransformer.addSliderValue( stepValue, 0 ) ) {
//            return;
//        }
//    }
//    update();
//    emit valueChanged( d->controllerTransformer.getValue(0) );
//    if( d->emitSliderValue ) {
//        const auto sliderValue = d->controllerTransformer.getSliderValue(0);
//        emit sliderPositionChanged( d->invertSliderValue ? QyBase::maximumSlider - sliderValue : sliderValue );
//    }
//}

// not needed here
//bool QyAbstractController::event(QEvent *e)
//{
//    return QWidget::event(e);
//}

void QyAbstractController::initTransformParameters( double p0, double p1 )
{
    Q_D(QyAbstractController);
    d->controllerTransformer.initTransformParameters(p0,p1);
}

bool QyAbstractController::registerTransformFunctions(
        QyBase::TransfomerParameters::FpSlider2value slider2value,
        QyBase::TransfomerParameters::FpValue2slider value2slider,
        QyBase::TransfomerParameters::FpSetMinMax setValueRange )
{
    Q_D(QyAbstractController);
    return d->controllerTransformer.registerTransformFunctions(slider2value, value2slider, setValueRange);
}

QT_END_NAMESPACE

