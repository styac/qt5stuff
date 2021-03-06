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

#include "QsPasswordInput.h"
#include "pwstring.h"

#include <private/qwidget_p.h>

QT_BEGIN_NAMESPACE

class QsPasswordInputPrivate : public QWidgetPrivate
{
    Q_DECLARE_PUBLIC(QsPasswordInput)

public:
    static constexpr int defaultPasswordBufferLength = 4*QsPasswordInput::maxPasswordLengthLimit; // UTF-8 max 4 byte/char
    static constexpr int verticalMargin = 1;    // qlineedit
    static constexpr int horizontalMargin = 2;  // qlineedit

    QsPasswordInputPrivate()
    : QWidgetPrivate()
    , password(defaultPasswordBufferLength)
    , passwordCompare(nullptr)
    , colorCurrentPW()
    , colorCorrectPW(Qt::green)
    , colorWrongPW(Qt::red)
    , maxLength(QsPasswordInput::maxPasswordLengthLimit)
    , minLength(QsPasswordInput::minPasswordLengthLimit)
    , flags(0)
    , leftTextMargin(0)
    , topTextMargin(0)
    , rightTextMargin(0)
    , bottomTextMargin(0)
//    , leftTextMargin(horizontalMargin)
//    , topTextMargin(verticalMargin)
//    , rightTextMargin(horizontalMargin)
//    , bottomTextMargin(verticalMargin)
    , hideCharacter('*')
    , normalization(QString::NormalizationForm_KC)
    {
        frame = true;
    }

    ~QsPasswordInputPrivate()
    {
        if( passwordCompare != nullptr ) {
            delete passwordCompare;
        }
    }

    void processInputMethodEvent( QInputMethodEvent *e );

    bool clipboardPaste();

    // password storage
    PWstring   password;
    PWstring   * passwordCompare;

    // attributes
    QColor  colorCurrentPW;
    QColor  colorCorrectPW;
    QColor  colorWrongPW;
    uint    maxLength;
    uint    minLength;

    union {
        uint16_t flags;
        struct {
            uint16_t frame                  : 1;
            uint16_t showPassword           : 1;
            uint16_t clipboardEnabled       : 1;
            uint16_t compareMode            : 1;
        };
    };

    // QMargins margins;
    int     leftTextMargin;
    int     topTextMargin;
    int     rightTextMargin;
    int     bottomTextMargin;
    QChar   hideCharacter;
    int     normalization;  // -1 no normalization
};

QT_END_NAMESPACE
