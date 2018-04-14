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

#include "QyController.h"
#include "QyController_p.h"
#include "QyStyleOption.h"
#include "QyClipboard.h"

#include <QToolTip>

QT_BEGIN_NAMESPACE

void drawQyMinimalStyle( const QyStyleOption *option, QPainter *p );

void QyControllerPrivate::init()
{
    Q_Q(QyController);
    q->setFocusPolicy(Qt::WheelFocus);
}

void QyController::initStyleOption( QyStyleOption *option) const
{
    if (!option)
        return;
    Q_D(const QyController);
    option->initFrom(this);
    option->valueDisplay = &(d->valueVector);
    option->styleData = &(d->styleData);
}

QyController::QyController( QWidget *parent )
    : QyAbstractController(*new QyControllerPrivate, parent)
{
    Q_D(QyController);
    d->init();
}

QyController::QyController( int valueId, int userEventValue, QWidget *parent )
    : QyAbstractController(*new QyControllerPrivate, parent)
{
    Q_D(QyController);
    d->init();
    d->valueId = valueId;
    d->userEventValue = userEventValue;
}

QyController::~QyController()
{
}

void QyController::resizeEvent(QResizeEvent *e)
{
    Q_D(QyController);
    d->recalculateStyleData(this);
    QWidget::resizeEvent(e);
    qDebug() << " ** resizeEvent";
}


void QyController::paintEvent(QPaintEvent * e)
{
    QPainter p(this);
    QyStyleOption option;
    initStyleOption(&option);
    drawQyMinimalStyle(&option, &p);
    qDebug() << " ** paintEvent: " << e ;
}

void QyController::mouseDoubleClickEvent(QMouseEvent * e)
{
    Q_D(QyController);
    if( d->remoteControlled ) {
        return;
    }

    d->controllerTransformer.reset();
    update();
    emit valueChanged( d->controllerTransformer.getValue(0), d->valueId);
    if( d->emitSliderValue ) {
        const auto sliderValue = d->controllerTransformer.getSliderValue(0);
        emit sliderPositionChanged( d->invertSliderValue ? QyBase::maximumSlider - sliderValue : sliderValue );
    }
}

void QyController::mousePressEvent(QMouseEvent * e)
{
    Q_D(QyController);
    d->lastPosition = - e->localPos().y() ;
    if( e->button() == Qt::MiddleButton ) {
        e->accept();
        auto kMods = QGuiApplication::keyboardModifiers();
        int keyModsInt = ( kMods & Qt::ShiftModifier ? 1 : 0 ) + ( kMods & Qt::ControlModifier ? 2 : 0 );
        emit userEvent( d->userEventValue, keyModsInt );
        return;
    }

//    if( d->remoteControlled ) {
//        return;
//    }

//    if( e->button() != Qt::LeftButton ) {
//        e->ignore();
//        return;
//    }
//    e->accept();
}

void QyController::mouseReleaseEvent(QMouseEvent * e)
{
    Q_D(QyController);
    if (e->buttons() & (~e->button()) ||
       (e->button() != Qt::LeftButton)) {
        e->ignore();
        return;
    }
    e->accept();
}

void QyController::mouseMoveEvent(QMouseEvent * e)
{
    Q_D(QyController);
    if( d->remoteControlled ) {
        return;
    }

    if (!(e->buttons() & Qt::LeftButton)) {
        e->ignore();
        return;
    }
    e->accept();

    if( d->pressed ) {
        d->pressed = false;
        d->lastPosition = - e->localPos().y();
    } else if( d->valueFromPoint( - e->localPos().y() ) ) {
        update();
        emit valueChanged( d->controllerTransformer.getValue(0), d->valueId);
        if( d->emitSliderValue ) {
            const auto sliderValue = d->controllerTransformer.getSliderValue(0);
            emit sliderPositionChanged( d->invertSliderValue ? QyBase::maximumSlider - sliderValue : sliderValue );
        }
    }
}

void QyController::wheelEvent(QWheelEvent *e)
{
    Q_D(QyController);
    e->accept();
}

QSize QyController::minimumSizeHint() const
{
    qDebug() << " ** minimumSizeHint";
    return QSize(50, 50);
}

QSize QyController::sizeHint() const
{
    qDebug() << " ** sizeHint" ;
    return QSize(100, 100).expandedTo(QApplication::globalStrut());
}

bool QyController::event(QEvent *e)
{
    return QyAbstractController::event(e);
}

void QyController::enterEvent(QEvent *e)
{
    qDebug() << " ** enterEvent: " << e ;
//    QToolTip::showText( this->pos(), "test" );
// or status
    update();
}

void QyController::leaveEvent(QEvent *e)
{
    qDebug() << " ** leaveEvent: " << e ;
    update();
}

// userEvent : Key_Delete -- not really used for other activity
void QyController::keyPressEvent(QKeyEvent *ev)
{
    auto kMods = QGuiApplication::keyboardModifiers();
    auto key = ev->key();
    Q_D(QyAbstractController);
    switch( key ) {
        case Qt::Key_Delete:
        if( ev->isAutoRepeat() ) {
            return; // do not send repeated events
        }
        int keyModsInt = ( kMods & Qt::ShiftModifier ? 1 : 0 ) + ( kMods & Qt::ControlModifier ? 2 : 0 );
        emit userEvent( d->userEventValue, keyModsInt );
        return;
    }

#if QyClipboard_use==1
    if(( kMods & Qt::ControlModifier ) && ( key == Qt::Key_C )) {
        // clipboard copy
        QString text;
        valueToClipboardFormat( text );
        QyClipboard::copy( text );
        ev->accept();
        return;
    }
#endif

    if( d->remoteControlled ) {
        return;
    }

    int32_t stepValue = 0;
    if( ev->modifiers() & Qt::ShiftModifier ) {
        switch (ev->key()) {
        case Qt::Key_Down:
            stepValue = - d->valueHandler.getStepValue(QyBase::STEPS::STEP_SINGLE_PLUS);
            break;
        case Qt::Key_Left:
            stepValue = - d->valueHandler.getStepValue(QyBase::STEPS::STEP_TINY_PLUS);
            break;
        case Qt::Key_Up:
            stepValue = d->valueHandler.getStepValue(QyBase::STEPS::STEP_SINGLE_PLUS);
            break;
        case Qt::Key_Right:
            stepValue = d->valueHandler.getStepValue(QyBase::STEPS::STEP_TINY_PLUS);
            break;
        case Qt::Key_PageUp:
            d->controllerTransformer.stepGiant( d->valueHandler.getStepValue(QyBase::STEPS::STEP_PAGE));
            break;
        case Qt::Key_PageDown:
            d->controllerTransformer.stepGiant( -d->valueHandler.getStepValue(QyBase::STEPS::STEP_PAGE));
            break;
        case Qt::Key_Home:
            d->controllerTransformer.reset();
            break;
        case Qt::Key_End:
            // define a flag to enable
            // no  for symmetric
            break;
        default:
            ev->ignore();
            return;
        }

    } else if( !( kMods & Qt::ControlModifier ) )  {

        // TODO : check no other modifier
        switch (ev->key()) {
        case Qt::Key_Down:
            stepValue = - d->valueHandler.getStepValue(QyBase::STEPS::STEP_SINGLE);
            break;
        case Qt::Key_Left:
            stepValue = - d->valueHandler.getStepValue(QyBase::STEPS::STEP_TINY);
            break;
        case Qt::Key_Up:
            stepValue = d->valueHandler.getStepValue(QyBase::STEPS::STEP_SINGLE);
            break;
        case Qt::Key_Right:
            stepValue = d->valueHandler.getStepValue(QyBase::STEPS::STEP_TINY);
            break;
        case Qt::Key_PageUp:
            stepValue = d->valueHandler.getStepValue(QyBase::STEPS::STEP_PAGE);
            break;
        case Qt::Key_PageDown:
            stepValue = - d->valueHandler.getStepValue(QyBase::STEPS::STEP_PAGE);
            break;
        case Qt::Key_Home:
            d->controllerTransformer.reset();
            break;
        case Qt::Key_End:
            // no  for symmetric
            // define a flag to enable
            break;
        default:
            ev->ignore();
            return;
        }
    }

    if( stepValue ) {
        if( ! d->controllerTransformer.addSliderValue( stepValue, 0 ) ) {
            return;
        }
    } else {
#if QyClipboard_use==1
        if(( kMods & Qt::ControlModifier ) && ( key == Qt::Key_V )) {
            valueFromClipboardFormat( QyClipboard::past() );
        }
#endif
    }

    update();
    emit valueChanged( d->controllerTransformer.getValue(0), d->valueId );
    if( d->emitSliderValue ) {
        const auto sliderValue = d->controllerTransformer.getSliderValue(0);
        emit sliderPositionChanged( d->invertSliderValue ? QyBase::maximumSlider - sliderValue : sliderValue );
    }
}

QT_END_NAMESPACE

