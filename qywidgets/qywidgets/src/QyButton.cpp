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

#include "QyButton.h"
#include "QyButton_p.h"
#include "QyColors.h"

#include <qapplication.h>
#include "qevent.h"
#include "qdebug.h"
#ifndef QT_NO_ACCESSIBILITY
#include "qaccessible.h"
#endif
#include <limits.h>

#include "QyButton_p.h"


QT_BEGIN_NAMESPACE

void drawQyMinimalStyle( const QyStyleOptionButton *opt, QPainter *p );


QyButtonPrivate::QyButtonPrivate()
    : QyAbstractButtonPrivate()
{
}

QyButtonPrivate::~QyButtonPrivate()
{
}


QyButton::QyButton(QWidget *parent)
    : QyAbstractButton(*new QyButtonPrivate, parent)
{
    Q_D(QyButton);
//    d->init();
}

QyButton::QyButton( int groupIndex, QWidget *parent )
    : QyAbstractButton(*new QyButtonPrivate, parent)
{
    Q_D(QyButton);
//    d->init();
    d->groupIndex = groupIndex;
}

QyButton::~QyButton()
{
}


void QyButton::resizeEvent(QResizeEvent *e)
{
    Q_D(QyButton);
//    d->recalculateStyleData(this);
//    QWidget::resizeEvent(e);
    qDebug() << "QyButton ** resizeEvent";
}

void QyButton::initStyleOption( QyStyleOptionButton *option) const
{
    if (!option)
        return;

    Q_D(const QyButton);
    option->initFrom(this);
    option->styleData = &(d->styleData);
}


void QyButton::paintEvent(QPaintEvent * e)
{
    QPainter p(this);
    QyStyleOptionButton option;
    initStyleOption(&option);
    drawQyMinimalStyle(&option, &p);
    qDebug() << "QyButton ** paintEvent: " << e ;
}

//void QyButton::mouseDoubleClickEvent(QMouseEvent * e)
//{
//    Q_D(QyButton);
//    if( d->remoteControlled ) {
//        return;
//    }

//    d->controllerTransformer.reset();
//    update();
//    emit valueChanged( d->controllerTransformer.getValue(0), d->id);
//    if( d->emitSliderValue ) {
//        const auto sliderValue = d->controllerTransformer.getSliderValue(0);
//        emit sliderPositionChanged( d->invertEmitSliderPos ? QyBase::maximumSlider - sliderValue : sliderValue );
//    }
//}

void QyButton::mousePressEvent(QMouseEvent * e)
{
    Q_D(QyButton);
    qDebug() << "QyButton ** mousePressEvent: " << e ;

    if( e->button() == Qt::MiddleButton ) {
        e->accept();
        auto kMods = QGuiApplication::keyboardModifiers();
        int opc = ( kMods & Qt::ShiftModifier ? 1 : 0 ) + ( kMods & Qt::ControlModifier ? 2 : 0 );
        if( kMods & Qt::ShiftModifier ) {
            d->extraState.s1 ^= 1;
        }
        if( kMods & Qt::ControlModifier ) {
            d->extraState.s0 ^= 1;
        }
        emit controlClicked( opc, d->extraState.s0, d->extraState.s1,  d->id, d->groupIndex );
        return;
    }

//    d->lastPosition = - e->localPos().y() ;
//    if( e->button() == Qt::MiddleButton ) {
//        e->accept();
//        auto kMods = QGuiApplication::keyboardModifiers();
//        int opc = ( kMods & Qt::ShiftModifier ? 1 : 0 ) + ( kMods & Qt::ControlModifier ? 2 : 0 );
//        if( kMods & Qt::ShiftModifier ) {
//            d->switchShift ^= 1;
//        }
//        if( kMods & Qt::ControlModifier ) {
//            d->switchCtrl ^= 1;
//        }
//        emit clicked( opc, d->switchCtrl, d->switchShift,  d->id );
//        return;
//    }

//    if( d->remoteControlled ) {
//        return;
//    }

//    if( e->button() != Qt::LeftButton ) {
//        e->ignore();
//        return;
//    }
//    e->accept();
}

void QyButton::mouseReleaseEvent(QMouseEvent * e)
{
    Q_D(QyButton);
    if (e->buttons() & (~e->button()) ||
       (e->button() != Qt::LeftButton)) {
        e->ignore();
        return;
    }
    e->accept();
    update();
}

//void QyButton::mouseMoveEvent(QMouseEvent * e)
//{
//    Q_D(QyButton);
//    if( d->remoteControlled ) {
//        return;
//    }

//    if (!(e->buttons() & Qt::LeftButton)) {
//        e->ignore();
//        return;
//    }
//    e->accept();

//    if( d->pressed ) {
//        d->pressed = false;
//        d->lastPosition = - e->localPos().y();
//    } else if( d->valueFromPoint( - e->localPos().y() ) ) {
//        update();
//        emit valueChanged( d->controllerTransformer.getValue(0), d->id);
//        if( d->emitSliderValue ) {
//            const auto sliderValue = d->controllerTransformer.getSliderValue(0);
//            emit sliderPositionChanged( d->invertEmitSliderPos ? QyBase::maximumSlider - sliderValue : sliderValue );
//        }
//    }
//}

//void QyButton::wheelEvent(QWheelEvent *e)
//{
//    Q_D(QyButton);
//    e->accept();
//}

QSize QyButton::minimumSizeHint() const
{
    Q_D(const QyButton);
    qDebug() << "QyButton ** minimumSizeHint";
    return QSize();
    //return d->styleData.minimumSizeHint;
}

QSize QyButton::sizeHint() const
{
    Q_D(const QyButton);
    qDebug() << "QyButton ** sizeHint" ;
    return QSize(100, 100).expandedTo(QApplication::globalStrut());
}

//bool QyButton::event(QEvent *e)
//{
//    return QyAbstractController::event(e);
//}

void QyButton::enterEvent(QEvent *e)
{
//    auto ev = static_cast<QEnterEvent *>(e);
    qDebug() << "QyButton ** enterEvent: " << e ;
//    QToolTip::showText( QWidget::mapToGlobal(this->pos() ) , "-----test-----" );
// or status
//    update();
}

void QyButton::leaveEvent(QEvent *e)
{
    qDebug() << "QyButton ** leaveEvent: " << e ;
//    update();
}

void QyButton::keyPressEvent(QKeyEvent *ev)
{
    auto kMods = QGuiApplication::keyboardModifiers();
    auto key = ev->key();
    if( ev->isAutoRepeat() ) {
        return; // do not send repeated events
    }
    Q_D(QyButton);

    switch( key ) {
    case Qt::Key_Insert:
        int opc = ( kMods & Qt::ShiftModifier ? 1 : 0 ) + ( kMods & Qt::ControlModifier ? 2 : 0 );
        if( kMods & Qt::ShiftModifier ) {
            d->extraState.s1 ^= 1;
        }
        if( kMods & Qt::ControlModifier ) {
            d->extraState.s0 ^= 1;
        }
        emit controlClicked( opc, d->extraState.s0, d->extraState.s1,  d->id, d->groupIndex );
        return;

        // clicked?
        return;
    }


    if( d->extraState.remoteControlled ) {
        return;
    }

    switch( key ) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
//        emit clicked( opc, d->switchCtrl, d->switchShift,  d->id );
        //    update();
        return;



// TAB, SHIFT TAB -> next,previous for group
    }
}

QT_END_NAMESPACE

