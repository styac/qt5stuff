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

#include <QtWidgets/qwidget.h>
#include <QColor>

QT_BEGIN_NAMESPACE

class QyButtonVector;
class QyAbstractButtonPrivate;

class QYWIDGET_LIBSHARED_EXPORT QyAbstractButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY( int id READ id WRITE setId )
    Q_PROPERTY( bool checked READ checked WRITE setChecked )
    Q_PROPERTY( bool hoverable READ hoverable WRITE setHoverable )
    Q_PROPERTY( bool toggleable READ toggleable WRITE setToggleable )
//    Q_PROPERTY( bool controlState0 READ controlState0 WRITE setControlState0 )
//    Q_PROPERTY( bool controlState1 READ controlState1 WRITE setControlState1 )
    Q_PROPERTY( QString text READ text WRITE setText)
    Q_PROPERTY( QColor stateOnColor READ stateOnColor WRITE setStateOnColor )
    Q_PROPERTY( QColor stateOffColor READ stateOffColor WRITE setStateOffColor )


public:
    friend class QyButtonVector;

    int id() const;
    int groupIndex() const;
    bool checked() const;
    bool hoverable() const;
    bool toggleable() const;


    void setId(int);
    void setText(QString const&);
    void setHoverable(bool);
//    void setExclusiveControl(bool);

    void setStateOnColor(QColor const&);
    void setStateOffColor(QColor const&);

    QString const& text() const;
    QColor const& stateOnColor() const;
    QColor const& stateOffColor() const;

public Q_SLOTS:
    void setChecked(bool);  // for toggleable

//    void clearChecked();    // for exclusive group - no signal sent !

Q_SIGNALS:
    void clicked( bool state, int id );
    void hoverEntered( int id );
    void hoverLeft( int id );
    void pressed( int id );
    void released( int id );

    // sent by middle mouse click and Key_Insert
    // opcode = 0..3 (shift=1, ctrl=2, shift+ctrl=3)

    void controlClicked( int opcode, bool state0, bool state1, int id );

protected:
    QyAbstractButton(QyAbstractButtonPrivate &dd, QWidget *parent = nullptr);
    ~QyAbstractButton();

    void setToggleable(bool);
    void setGroupIndex(int);


private:
    Q_DISABLE_COPY(QyAbstractButton)
    Q_DECLARE_PRIVATE(QyAbstractButton)
};

QT_END_NAMESPACE

