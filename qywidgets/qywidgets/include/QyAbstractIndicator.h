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
#include "QyEnums.h"
#include "QyTypes.h"
#include "QyGlobal.h"

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qframe.h>
#include <QColor>

QT_BEGIN_NAMESPACE

class QyAbstractIndicatorPrivate;

class QYWIDGET_LIBSHARED_EXPORT QyAbstractIndicator : public QFrame
{
    Q_OBJECT
    Q_PROPERTY( bool mirrored READ mirrored WRITE setMirrored )
    Q_PROPERTY( bool invertedFlow READ invertedFlow WRITE setInvertedFlow )
    Q_PROPERTY( bool symmetric READ symmetric WRITE setSymmetric)
    Q_PROPERTY( Qt::Orientation orientation READ orientation WRITE setOrientation )
    Q_PROPERTY( Qt::Orientation sequenceOrientation READ sequenceOrientation WRITE setSequenceOrientation )
    Q_PROPERTY( double minimum READ minimum WRITE setMinimum)
    Q_PROPERTY( double maximum READ maximum WRITE setMaximum)
    Q_PROPERTY( Qy::GraphicStyle graphicStyle READ graphicStyle WRITE setGraphicStyle)
    Q_PROPERTY( Qy::TextBoxPlacement textBoxPlacement READ textBoxPlacement WRITE setTextBoxPlacement)
    Q_PROPERTY( Qy::ColorStyle colorStyle READ colorStyle WRITE setColorStyle)
    Q_PROPERTY( QString caption READ caption WRITE setCaption)
    Q_PROPERTY( QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY( QColor rightColor READ rightColor WRITE setRightColor )
    Q_PROPERTY( QColor leftColor READ leftColor WRITE setLeftColor )

public:
    ~QyAbstractIndicator();

    void initTransformParameters( double p0, double p1 );

    bool registerTransformFunctions(
            QyBase::TransfomerParameters::FpSlider2value slider2value,
            QyBase::TransfomerParameters::FpValue2slider value2slider,
            QyBase::TransfomerParameters::FpSetMinMax setValueRange );

    void setCaption(QString const&);
    void setSuffix(QString const&, uint8_t);
    void setMinimum(double);
    void setMaximum(double);
    void setSymmetric(bool);
    void setMirrored( bool );
    void setInvertedFlow( bool );
    void setGraphicStyle(Qy::GraphicStyle);
    void setTextBoxPlacement(Qy::TextBoxPlacement);
    void setColorStyle(Qy::ColorStyle);
    void setOrientation(Qt::Orientation);
    void setSequenceOrientation(Qt::Orientation);

    void setTextColor(QColor const&);
    void setRightColor(QColor const&);
    void setLeftColor(QColor const&);

    QString const& caption() const;
    QString const& suffix( uint8_t ) const;
    bool symmetric() const;
    bool mirrored() const;
    bool invertedFlow() const;
    double minimum() const;
    double maximum() const;
    double value(int) const;
    Qt::Orientation orientation() const;
    Qt::Orientation sequenceOrientation() const;
    Qy::GraphicStyle graphicStyle() const;
    Qy::TextBoxPlacement textBoxPlacement() const;
    Qy::ColorStyle colorStyle() const;

    QColor const& textColor() const;
    QColor const& rightColor() const;
    QColor const& leftColor() const;

public Q_SLOTS:
    void setValue(double,int);
    void setRange(double min, double max);

protected:
    QyAbstractIndicator(QyAbstractIndicatorPrivate &dd, QWidget *parent = nullptr);

private:
    Q_DISABLE_COPY(QyAbstractIndicator)
    Q_DECLARE_PRIVATE(QyAbstractIndicator)
};

QT_END_NAMESPACE

