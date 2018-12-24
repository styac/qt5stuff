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

#include "QsGlobal.h"

#include <QtWidgets/qtwidgetsglobal.h>
#include <QtWidgets/qframe.h>
#include <QtGui/qtextcursor.h>
#include <QtCore/qstring.h>
#include <QtCore/qmargins.h>

QT_BEGIN_NAMESPACE

class QStyleOptionFrame;
class QsPasswordInputPrivate;

class QSPASSWORDINPUT_LIBSHARED_EXPORT QsPasswordInput : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int maxLength READ maxLength WRITE setMaxLength)
    Q_PROPERTY(int minLength READ minLength WRITE setMinLength)
    Q_PROPERTY(QString::NormalizationForm normalization READ normalization WRITE setNormalization )
//    Q_PROPERTY(bool checkLength READ checkLength WRITE setCheckLength)
    Q_PROPERTY(bool frame READ hasFrame WRITE setFrame)
    Q_PROPERTY(bool clipboardEnabled READ clipboardEnabled WRITE setClipboardEnabled)
    Q_PROPERTY(bool passwordOk READ passwordOk WRITE setPasswordOk)

public:
    static constexpr int minPasswordLengthLimit = 4;
    static constexpr int maxPasswordLengthLimit = 256;

    explicit QsPasswordInput( QWidget *parent = nullptr );

    ~QsPasswordInput();

    void text( std::string& password, bool deleteContent );

    void setMaxLength(int);

    void setMinLength(int);

    int maxLength() const;

    int minLength() const;

    void setNormalization(QString::NormalizationForm );

    QString::NormalizationForm normalization() const;

    void setFrame(bool);

    bool hasFrame() const;

    void setClipboardEnabled(bool);

    bool clipboardEnabled() const;

    bool passwordOk() const;

    void setTextMargins(int left, int top, int right, int bottom);

    void setTextMargins(const QMargins &margins);

    void getTextMargins(int *left, int *top, int *right, int *bottom) const;

    QMargins textMargins() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

public Q_SLOTS:
    void setPasswordOk(bool);
    void shred();
    void clear();

Q_SIGNALS:
    void returnPressed();
    void passwordTooLong();
    void passwordTooShort();
    void textChanged(); // not emitted yet

public:
    bool event(QEvent *) Q_DECL_OVERRIDE;

protected:
    // virtuals
    void mousePressEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *) Q_DECL_OVERRIDE;
    void focusInEvent(QFocusEvent *) Q_DECL_OVERRIDE;
    void focusOutEvent(QFocusEvent *) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
    void changeEvent(QEvent *) Q_DECL_OVERRIDE;
    void inputMethodEvent(QInputMethodEvent *) Q_DECL_OVERRIDE;
    void initStyleOption(QStyleOptionFrame *option) const;

private:    
    Q_DECLARE_PRIVATE(QsPasswordInput)
    Q_DISABLE_COPY(QsPasswordInput)
};

QT_END_NAMESPACE


