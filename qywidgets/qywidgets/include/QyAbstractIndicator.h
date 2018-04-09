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

// https://wiki.qt.io/How_to_create_a_library_with_Qt_and_use_it_in_an_application
// http://doc.qt.io/qt-5/sharedlibrary.html

#include "QyTransfomerParameters.h"
#include "QyEnums.h"
#include "QyTypes.h"
#include "QyGlobal.h"

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qframe.h>

QT_BEGIN_NAMESPACE

class QyAbstractIndicatorPrivate;

class QYWIDGET_LIBSHARED_EXPORT QyAbstractIndicator : public QFrame
{
    Q_OBJECT
    Q_PROPERTY( bool mirrored READ mirrored WRITE setMirrored )
    Q_PROPERTY( bool invertedFlow READ invertedFlow WRITE setInvertedFlow )
    Q_PROPERTY( bool symmetric READ symmetric WRITE setSymmetric)
    Q_PROPERTY( Qt::Orientation orientation READ orientation WRITE setOrientation )
    // to QyIndicator
    Q_PROPERTY( Qt::Orientation sequenceOrientation READ sequenceOrientation WRITE setSequenceOrientation )
    Q_PROPERTY( double minimum READ minimum WRITE setMinimum)
    Q_PROPERTY( double maximum READ maximum WRITE setMaximum)
//    Q_PROPERTY( QyBase::ValueIO value READ value WRITE setValue)
    //Q_PROPERTY( double value READ value WRITE setValue)
    Q_PROPERTY( Qy::GraphicStyle graphicStyle READ graphicStyle WRITE setGraphicStyle)
    Q_PROPERTY( Qy::TextBoxPlacement textBoxPlacement READ textBoxPlacement WRITE setTextBoxPlacement)
    Q_PROPERTY( Qy::ColorStyle colorStyle READ colorStyle WRITE setColorStyle)

//    Q_PROPERTY(QColor textColor READ textColor WRITE setValueColor)
//    Q_PROPERTY( Qt::QColor rightColor READ rightColor WRITE setRightColor )
//    Q_PROPERTY( Qt::QColor leftColor READ lettColor WRITE setLeftColor )

public:
    ~QyAbstractIndicator();

    void initTransformParameters( double p0, double p1 );

    bool registerTransformFunctions(
            QyBase::TransfomerParameters::FpSlider2value slider2value,
            QyBase::TransfomerParameters::FpValue2slider value2slider,
            QyBase::TransfomerParameters::FpSetMinMax setValueRange );

    void setMinimum(double);
    void setMaximum(double);
    void setSymmetric(bool);
    void setMirrored( bool );
    void setInvertedFlow( bool );
    void setGraphicStyle(Qy::GraphicStyle);
    void setTextBoxPlacement(Qy::TextBoxPlacement);
    void setColorStyle(Qy::ColorStyle);
    void setOrientation(Qt::Orientation);
    // to QyIndicator
    void setSequenceOrientation(Qt::Orientation);

    bool symmetric() const;
    bool mirrored() const;
    bool invertedFlow() const;
    double minimum() const;
    double maximum() const;
//    QyBase::ValueIO value() const;
    double value(int) const;
    Qt::Orientation orientation() const;
    // to QyIndicator
    Qt::Orientation sequenceOrientation() const;
    Qy::GraphicStyle graphicStyle() const;
    Qy::TextBoxPlacement textBoxPlacement() const;
    Qy::ColorStyle colorStyle() const;

public Q_SLOTS:
    void setValue(double,int);
//    void setValue(const QyBase::ValueIO&);
    void setRange(double min, double max);

protected:
    QyAbstractIndicator(QyAbstractIndicatorPrivate &dd, QWidget *parent = nullptr);

private:
    Q_DISABLE_COPY(QyAbstractIndicator)
    Q_DECLARE_PRIVATE(QyAbstractIndicator)
};

QT_END_NAMESPACE

