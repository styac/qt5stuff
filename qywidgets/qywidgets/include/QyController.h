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


//void QProgressBarPrivate::init()
//{
//    Q_Q(QProgressBar);
//    QSizePolicy sp(QSizePolicy::Expanding, QSizePolicy::Fixed);
//    if (orientation == Qt::Vertical)
//        sp.transpose();
//    q->setSizePolicy(sp);
//    q->setAttribute(Qt::WA_WState_OwnSizePolicy, false);
//    resetLayoutItemMargins();
//}

//QSize QProgressBar::minimumSizeHint() const
//{
//    QSize size;
//    if (orientation() == Qt::Horizontal)
//        size = QSize(sizeHint().width(), fontMetrics().height() + 2);
//    else
//        size = QSize(fontMetrics().height() + 2, sizeHint().height());
//    return size;
//}


//void QProgressBar::setOrientation(Qt::Orientation orientation)
//{
//    Q_D(QProgressBar);
//    if (d->orientation == orientation)
//        return;
//    d->orientation = orientation;
//    if (!testAttribute(Qt::WA_WState_OwnSizePolicy)) {
//        setSizePolicy(sizePolicy().transposed());
//        setAttribute(Qt::WA_WState_OwnSizePolicy, false);
//    }
//    d->resetLayoutItemMargins();
//    update();
//    updateGeometry();
//}

#include "QyAbstractController.h"

QT_BEGIN_NAMESPACE

class QyControllerPrivate;
class QyStyleOption;

class QYWIDGET_LIBSHARED_EXPORT QyController: public QyAbstractController
{
    Q_OBJECT

public:
    explicit QyController( QWidget *parent = nullptr );
    QyController( int valueId, int userEventValue, QWidget *parent = nullptr);

    ~QyController();

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

Q_SIGNALS:
    // sent by middle mouse click and Key_Delete
    // userEventValue is settable
    // keyMod = 0..3 (shift=1, ctrl=2, shift+ctrl=3)
    // onoff - every 2nd for all 4 cases
    void userEvent( int opcode, bool switchCtrl, bool switchShift, int userEventValue );

protected:
    void keyPressEvent(QKeyEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void initStyleOption(QyStyleOption *opt) const;
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;

    // TODO check what is needed -- +implemenet toolTip, StatusTip
    bool event(QEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;
    void enterEvent(QEvent *e) override;
    void leaveEvent(QEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    Q_DECLARE_PRIVATE(QyController)
    Q_DISABLE_COPY(QyController)
};

QT_END_NAMESPACE

