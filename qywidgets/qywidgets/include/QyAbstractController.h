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

#include "QyTransfomerParameters.h"
#include "QyAbstractIndicator.h"

QT_BEGIN_NAMESPACE

class QyAbstractControllerPrivate;

class QYWIDGET_LIBSHARED_EXPORT QyAbstractController : public QyAbstractIndicator
{
    Q_OBJECT
    Q_PROPERTY( bool symmetric READ symmetric WRITE setSymmetric )
    Q_PROPERTY( bool emitSliderValue READ emitSliderValue WRITE setEmitSliderValue )
    Q_PROPERTY( bool invertSetSliderPos READ invertSetSliderPos WRITE setInvertSetSliderPos )
    Q_PROPERTY( bool invertEmitSliderPos READ invertEmitSliderPos WRITE setInvertEmitSliderPos )
    Q_PROPERTY( bool remoteControlled READ remoteControlled WRITE setRemoteControlled )
    Q_PROPERTY( bool controlState0 READ controlState0 WRITE setControlState0 )
    Q_PROPERTY( bool controlState1 READ controlState1 WRITE setControlState1 )
    Q_PROPERTY( double minimum READ minimum WRITE setMinimum )
    Q_PROPERTY( double maximum READ maximum WRITE setMaximum )
    Q_PROPERTY( double value READ value WRITE setValue NOTIFY valueChanged USER true )
    Q_PROPERTY( int singleStep READ singleStep WRITE setSingleStep )
    Q_PROPERTY( int pageStep READ pageStep WRITE setPageStep )
    Q_PROPERTY( int sliderPosition READ sliderPosition WRITE setSliderPosition NOTIFY sliderPositionChanged )
    Q_PROPERTY( Qy::ValuePhysicalType valuePhysicalType READ valuePhysicalType WRITE setValuePhysicalType )
    Q_PROPERTY( QString suffix READ suffix WRITE setSuffix )

public:
    void setSymmetric(bool);
    void setControlState0(bool);
    void setControlState1(bool);
    void setControllerIndicator(bool);
    void setMinimum(double);
    void setMaximum(double);
    void setSingleStep(int);
    void setPageStep(int);
    void setValuePhysicalType(Qy::ValuePhysicalType);
    void setSuffix(QString const&);

    void initTransformParameters( double p0, double p1);
    bool registerTransformFunctions(
            QyBase::TransfomerParameters::FpSlider2value slider2value,
            QyBase::TransfomerParameters::FpValue2slider value2slider,
            QyBase::TransfomerParameters::FpSetMinMax setValueRange );

    Qt::Orientation orientation() const;
    bool symmetric() const;
    bool controlState0() const;
    bool controlState1() const;
    bool controllerIndicator() const;
    bool emitSliderValue() const;
    bool invertSetSliderPos() const;
    bool invertEmitSliderPos() const;
    bool remoteControlled() const;
    double minimum() const;
    double maximum() const;
    double value() const;
    int sliderMaximum() const;
    int sliderMinimum() const;
    int singleStep() const;
    int pageStep() const;
    int sliderPosition() const;
    Qy::ValuePhysicalType valuePhysicalType() const;
    QString const& suffix() const;

public Q_SLOTS:
    void setValue(double);
    void setSliderPosition(int);
    void setRange(double min, double max);
    void setEmitSliderValue(bool);
    void setInvertSetSliderPos(bool);
    void setInvertEmitSliderPos(bool);
    void setRemoteControlled(bool);

Q_SIGNALS:
    void sliderPositionChanged(int value);
    void valueChanged(double value, int valueId);
    void rangeChanged(int min, int max);

    // sent by middle mouse click and Key_Insert
    // opcode = 0..3 (shift=1, ctrl=2, shift+ctrl=3)

    void controlClicked( int opcode, bool state0, bool state1, int id, int goupIndex );

protected:
    ~QyAbstractController();
    // add id
    QyAbstractController(QyAbstractControllerPrivate &dd, QWidget *parent = nullptr);
    void valueToClipboardFormat( QString& res );
    bool valueFromClipboardFormat( const QString& res );

private:
    Q_DISABLE_COPY(QyAbstractController)
    Q_DECLARE_PRIVATE(QyAbstractController)
};

QT_END_NAMESPACE

