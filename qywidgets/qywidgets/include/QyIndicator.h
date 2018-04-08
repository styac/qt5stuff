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

#include "QyAbstractIndicator.h"
#include "QyTypes.h"

QT_BEGIN_NAMESPACE

class QyIndicatorPrivate;
class QyStyleOption;

class QYWIDGET_LIBSHARED_EXPORT QyIndicator: public QyAbstractIndicator
{
    Q_OBJECT
    Q_PROPERTY( uint vectorsize READ vectorsize WRITE setVectorsize )
    Q_PROPERTY( QyBase::ValueIO value READ value WRITE setValue )

public:
    explicit QyIndicator(QWidget *parent = nullptr);
    ~QyIndicator();

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QyBase::ValueIO value() const;

public Q_SLOTS:
    void setVectorsize( uint );
    uint vectorsize() const;
    void setValue(const QyBase::ValueIO& );

protected:
    bool event(QEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
//    void wheelEvent(QWheelEvent *e) override;
    void enterEvent(QEvent *e) override;
    void leaveEvent(QEvent *e) override;

    // what is needed ?
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
//    void mouseMoveEvent(QMouseEvent *e) override;
//    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void initStyleOption(QyStyleOption *opt) const;

private:
    Q_DECLARE_PRIVATE(QyIndicator)
    Q_DISABLE_COPY(QyIndicator)
};

QT_END_NAMESPACE

