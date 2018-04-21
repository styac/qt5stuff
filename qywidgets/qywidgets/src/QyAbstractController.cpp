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
    , remoteControlledColorAlpha(128)
    , valuePhysicalType(Qy::VPT_Number)
    , flags(0)
{
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

QyAbstractController::QyAbstractController(QyAbstractControllerPrivate &dd, QWidget *parent)
    : QyAbstractIndicator(dd, parent)
{
    Q_D(QyAbstractController);
    setSymmetric(false);
    d->styleData.setColors( d->leftColor, this->palette().color(QPalette::Window).darker() );
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
            emit valueChanged( d->controllerTransformer.getValue(0), d->valueId );
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

void QyAbstractController::setValuePhysicalType(Qy::ValuePhysicalType val)
{
    Q_D(QyAbstractController);
    d->valuePhysicalType = val;
}


int QyAbstractController::userEventValue() const
{
    Q_D(const QyAbstractController);
    return d->userEventValue;
}

Qy::ValuePhysicalType QyAbstractController::valuePhysicalType() const
{
    Q_D(const QyAbstractController);
    return d->valuePhysicalType;
}

void QyAbstractController::setSymmetric( bool val )
{
    constexpr int alphaEnabled = 255;
    constexpr int alphaDisabled = 64;
    Q_D(QyAbstractController);
    if( d->controllerTransformer.setSymmetric(val) ) {
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

void QyAbstractController::setSuffix(QString const& val )
{
    QyAbstractIndicator::setSuffix(val,0);
}

QString const& QyAbstractController::suffix() const
{
    return QyAbstractIndicator::suffix(0);
}

void QyAbstractController::setRemoteControlled(bool val)
{
    Q_D(QyAbstractController);
    if( d->remoteControlled != val ) {
        d->remoteControlled = val;
        d->styleData.remoteControlled = val;
        update();
    }
}

bool QyAbstractController::remoteControlled() const
{
    Q_D(const QyAbstractController);
    return d->remoteControlled;
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
        emit valueChanged( value, d->valueId );
        if( d->emitSliderValue ) {
            const auto sliderValue = d->controllerTransformer.getSliderValue(0);
            emit sliderPositionChanged( sliderValue ? QyBase::maximumSlider - sliderValue : sliderValue );
        }
    }
}

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
    // only if remote controlled
    if( ! d->remoteControlled ) {
        return;
    }

    const auto invert = d->invertSetSliderPos;
    const auto sliderVal = invert ? QyBase::maximumSlider - val : val;
    if( d->controllerTransformer.setSliderValue(sliderVal,0) ) {
        if( d->emitSliderValue ) {
            emit sliderPositionChanged( sliderVal );
        }
        emit valueChanged( d->controllerTransformer.getValue(0), d->valueId );
        update();
    }
}

bool QyAbstractController::emitSliderValue() const
{
    Q_D( const QyAbstractController);
    return d->emitSliderValue;
}

bool QyAbstractController::invertSetSliderPos() const
{
    Q_D( const QyAbstractController);
    return d->invertSetSliderPos;
}

bool QyAbstractController::invertEmitSliderPos() const
{
    Q_D( const QyAbstractController);
    return d->invertEmitSliderPos;
}

int QyAbstractController::valueId() const
{
    Q_D( const QyAbstractController);
    return d->valueId;
}

void QyAbstractController::setValueId(int val)
{
    Q_D(QyAbstractController);
    d->valueId = val;
}

void QyAbstractController::setEmitSliderValue(bool val)
{
    Q_D(QyAbstractController);
    if( d->emitSliderValue != val ) {
        d->emitSliderValue = val;
        if( val ) {
            const auto invert = d->invertSetSliderPos;
            const auto sliderValue = d->controllerTransformer.getSliderValue(0);
            emit sliderPositionChanged( invert ? QyBase::maximumSlider - sliderValue : sliderValue );
        }
    }
}

void QyAbstractController::setInvertSetSliderPos(bool val)
{
    Q_D(QyAbstractController);
    if( d->invertSetSliderPos != val ) {
        d->invertSetSliderPos = val;
        // refresh pos
        // update();
    }
}

void QyAbstractController::setInvertEmitSliderPos(bool val)
{
    Q_D(QyAbstractController);
    if( d->invertEmitSliderPos != val ) {
        d->invertEmitSliderPos = val;
        if( d->emitSliderValue ) {
            const auto sliderValue = d->controllerTransformer.getSliderValue(0);
            emit sliderPositionChanged( val ? QyBase::maximumSlider - sliderValue : sliderValue );
        }
        // refresh pos
        // update();
    }
}

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

void QyAbstractController::valueToClipboardFormat( QString& res )
{
    Q_D(QyAbstractController);
    QString caption( d->styleData.caption.size() ? d->styleData.caption : "_" );
    res.append( QString(
        "{ object : QyController ,"
        " type : %0 ,"
        " value : %1 ,"
        " caption : \"%2\" "
        "}"
        ).arg( d->valuePhysicalType ).arg( value() ).arg( caption ));
}

bool QyAbstractController::valueFromClipboardFormat( const QString& res )
{
    Q_D(QyAbstractController);
    int size = res.size();
    if( size < 20 ) { // check the valid minimum
        return false;
    }
    int posLeftTit = res.indexOf('{');
    if( posLeftTit < 0 ) {
        return false;
    }
    int posRigthTit = res.indexOf('}');
    if( posRigthTit < 0 ) {
        return false;
    }
    QStringRef subs(&res, posLeftTit + 1, posRigthTit - posLeftTit - 1);
    QStringList maps = subs.toString().split(',', QString::SkipEmptyParts);
    if( maps.size() < 4 ) {
        return false;
    }
    QStringList typeStr = maps[1].split(':', QString::SkipEmptyParts);
    if( typeStr[0].indexOf("type") < 0 ) { // use QRegularExpression
        return false;
    }
    QStringList valueStr = maps[2].split(':', QString::SkipEmptyParts);
    if( valueStr[0].indexOf("value") < 0 ) { // use QRegularExpression
        return false;
    }

    bool ok;
    int type = typeStr[1].toInt( &ok );
    if( ! ok ) {
        return false;
    }
    if( type == int(d->valuePhysicalType) ) {
        double value = valueStr[1].toDouble( &ok );
        if( ! ok ) {
            return false;
        }
        return d->controllerTransformer.setValue( value, 0 );
    }
    return false;
}


QT_END_NAMESPACE

