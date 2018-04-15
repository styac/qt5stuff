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

#include "QyIndicator_p.h"
#include "QyAbstractIndicator_p.h"
#include "QyStyleOption.h"

QT_BEGIN_NAMESPACE

void drawQyMinimalStyle( const QyStyleOption *option, QPainter *p );


void QyIndicatorPrivate::init()
{
    Q_Q(QyIndicator);
    q->setFocusPolicy(Qt::WheelFocus);
}

void QyIndicator::initStyleOption( QyStyleOption *option) const
{
    if (!option)
        return;

    Q_D(const QyIndicator);
    option->initFrom(this);
    option->valueDisplay = &(d->valueVector);
}

QyIndicator::QyIndicator(QWidget *parent)
    : QyAbstractIndicator(*new QyIndicatorPrivate, parent)
{
    Q_D(QyIndicator);
    d->init();
}

QyIndicator::~QyIndicator()
{
}

void QyIndicator::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}

void QyIndicator::paintEvent(QPaintEvent * e)
{
    QPainter p(this);
    QyStyleOption option;
    initStyleOption(&option);
    drawQyMinimalStyle(&option, &p);
//    qDebug() << " ** paintEvent: " << e ;
}

// does nothing
void QyIndicator::mousePressEvent(QMouseEvent * e)
{
    Q_D(QyIndicator);
    e->accept();
}

void QyIndicator::mouseReleaseEvent(QMouseEvent * e)
{
    Q_D(QyIndicator);
    if (e->buttons() & (~e->button()) ||
       (e->button() != Qt::LeftButton)) {
        e->ignore();
        return;
    }
    e->accept();
}

QSize QyIndicator::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize QyIndicator::sizeHint() const
{
    return QSize(100, 100).expandedTo(QApplication::globalStrut());
}

bool QyIndicator::event(QEvent *e)
{
    return QyAbstractIndicator::event(e);
}

void QyIndicator::enterEvent(QEvent *e)
{
    qDebug() << " ** enterEvent: " << e ;
}

void QyIndicator::leaveEvent(QEvent *e)
{

    qDebug() << " ** leaveEvent: " << e ;
}


void QyIndicator::setVectorsize( uint val )
{
    Q_D(QyIndicator);
    d->valueVector.setSize( val );
}

uint QyIndicator::vectorsize() const
{
    Q_D(const QyIndicator);
    return d->valueVector.getSize();
}

QyBase::ValueIO QyIndicator::value() const
{
    Q_D(const QyIndicator);
    return d->indicatorTransformer.getValue();
}

void QyIndicator::setValue(const QyBase::ValueIO& value)
{
    Q_D(QyIndicator);
    if( d->indicatorTransformer.setValue( value )) {
        update();
    }
}

QT_END_NAMESPACE

