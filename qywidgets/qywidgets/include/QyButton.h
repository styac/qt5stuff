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

#include "QyEnums.h"
#include "QyTypes.h"
#include "QyGlobal.h"
#include "QyAbstractButton.h"
#include "QyStyleOption.h"

QT_BEGIN_NAMESPACE

class QyButtonPrivate;

class QYWIDGET_LIBSHARED_EXPORT QyButton : public QyAbstractButton
{
    Q_OBJECT

public:
    explicit QyButton( QWidget *parent = nullptr );
    explicit QyButton( int groupIndex, QWidget *parent = nullptr);

    ~QyButton();

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected:
    QyButton(QyButtonPrivate &dd, QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent *ev) override;
//    void mouseMoveEvent(QMouseEvent *e) override;
//    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void initStyleOption(QyStyleOptionButton *opt) const;
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
//    bool event(QEvent *e) override;
//    void wheelEvent(QWheelEvent *e) override;
    void enterEvent(QEvent *e) override;
    void leaveEvent(QEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

Q_SIGNALS:
    // sent by middle mouse click and Key_Delete
    // userEventValue is settable
    // keyMod = 0..3 (shift=1, ctrl=2, shift+ctrl=3)
    // onoff - every 2nd for all 4 cases

    // TODO to abtract
    void controlClicked( int opcode, bool switchCtrl, bool switchShift, int id, int goupIndex );

private:
    Q_DISABLE_COPY(QyButton)
    Q_DECLARE_PRIVATE(QyButton)
};

QT_END_NAMESPACE

