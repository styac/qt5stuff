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


#include "QsPasswordInput_p.h"
#include "QsPasswordInput.h"
#include "utils.h"

#include <qpainter.h>
#include "qapplication.h"
#include "qdrawutil.h"
#include "qevent.h"
#include "qfontmetrics.h"
#include "qstylehints.h"
#include "qpainter.h"
#include "qstyle.h"
#include "qstyleoption.h"
#include "qvector.h"
#include "qdebug.h"
//#include "private/qstylesheetstyle_p.h"

#include <limits.h>
#include <iostream>

QT_BEGIN_NAMESPACE

// -----------------------------------------------------------------------------------
// QsPasswordInputPrivate
// -----------------------------------------------------------------------------------

// TODO: put to QsPasswordInput
void QsPasswordInputPrivate::init()
{
    Q_Q(QsPasswordInput);
    q->setFocusPolicy(Qt::StrongFocus);
    q->setAttribute(Qt::WA_InputMethodEnabled);
    q->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed, QSizePolicy::LineEdit));
    q->setBackgroundRole(QPalette::Base);
    q->setAttribute(Qt::WA_KeyCompression);
    q->setMouseTracking(true);
    q->setCursor(Qt::IBeamCursor);
    q->setAttribute(Qt::WA_MacShowFocusRect);
}


void QsPasswordInputPrivate::processInputMethodEvent( QInputMethodEvent *e )
{
    std::cout << "*** inputMethodEvent  not implemented" << std::endl;
}

// -----------------------------------------------------------------------------------
// QsPasswordInput
// -----------------------------------------------------------------------------------

QsPasswordInput::QsPasswordInput( QWidget *parent )
: QWidget( *new QsPasswordInputPrivate, parent, 0 )
{
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_InputMethodEnabled);
    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed, QSizePolicy::LineEdit));
    setBackgroundRole(QPalette::Base);
    setAttribute(Qt::WA_KeyCompression);
    setMouseTracking(true);
    setCursor(Qt::IBeamCursor);
    setAttribute(Qt::WA_MacShowFocusRect);
}

QsPasswordInput::~QsPasswordInput()
{}

void QsPasswordInput::initStyleOption(QStyleOptionFrame *option) const
{
    if (!option)
        return;
    Q_D(const QsPasswordInput);
    option->initFrom(this);
    option->rect = contentsRect();
    option->lineWidth = d->frame ? style()->pixelMetric(QStyle::PM_DefaultFrameWidth, option, this) : 0;
    option->midLineWidth = 0;
    option->state |= QStyle::State_Sunken;
    option->features = QStyleOptionFrame::None;
    option->frameShape = QFrame::Box;
}

void  QsPasswordInput::text( std::string& password, bool deleteContent )
{
    Q_D(QsPasswordInput);
    password.assign( d->password.data(), d->password.size() );
    if( deleteContent ) {
        d->password.shred();
    }
}

void  QsPasswordInput::shred()
{
    Q_D(QsPasswordInput);
    d->password.shred();
}

void  QsPasswordInput::clear()
{
    Q_D(QsPasswordInput);
    d->password.clear();
}

int QsPasswordInput::minLength() const
{
    Q_D(const QsPasswordInput);
    return d->minLength;
}

void QsPasswordInput::setMinLength(int val)
{
    Q_D(QsPasswordInput);
    d->minLength = val;
}

int QsPasswordInput::maxLength() const
{
    Q_D(const QsPasswordInput);
    return d->maxLength;
}

void QsPasswordInput::setMaxLength(int val)
{
    Q_D(QsPasswordInput);
    d->maxLength = val;
}

QString::NormalizationForm QsPasswordInput::normalization() const
{
    Q_D(const QsPasswordInput);
    return d->normalizationForm;
}

void QsPasswordInput::setNormalization(QString::NormalizationForm val)
{
    Q_D(QsPasswordInput);
    d->normalizationForm = val;
}

void QsPasswordInput::setClipboardEnabled(bool val)
{
    Q_D(QsPasswordInput);
    d->clipboardEnabled = val;
}

bool QsPasswordInput::passwordOk() const
{
    Q_D(const QsPasswordInput);
    return d->passwordOk;
}

void QsPasswordInput::setPasswordOk(bool val)
{
    Q_D(QsPasswordInput);
    d->passwordOk = val;
}

bool QsPasswordInput::clipboardEnabled() const
{
    Q_D(const QsPasswordInput);
    return d->clipboardEnabled;
}

bool QsPasswordInput::hasFrame() const
{
    Q_D(const QsPasswordInput);
    return d->frame;
}

void QsPasswordInput::setFrame(bool enable)
{
    Q_D(QsPasswordInput);
    d->frame = enable;
    update();
    updateGeometry();
}

QSize QsPasswordInput::sizeHint() const
{
    Q_D(const QsPasswordInput);
    ensurePolished();
    QFontMetrics fm(font());
    int h = qMax( fm.height(), 14 )
            + 2*d->verticalMargin
            + d->topTextMargin
            + d->bottomTextMargin
            + d->topmargin
            + d->bottommargin;

    int w = fm.width(QLatin1Char('x')) * 17
            + 2*d->horizontalMargin
            + d->leftTextMargin
            + d->rightTextMargin
            + d->leftmargin
            + d->rightmargin;

    QStyleOptionFrame opt;
    initStyleOption(&opt);
    return (style()->sizeFromContents(QStyle::CT_LineEdit, &opt,
        QSize(w, h).expandedTo(QApplication::globalStrut()), this));
}

QSize QsPasswordInput::minimumSizeHint() const
{
    Q_D(const QsPasswordInput);
    ensurePolished();
    QFontMetrics fm = fontMetrics();
    int h = fm.height()
            + qMax(2*d->verticalMargin, fm.leading())
            + d->topTextMargin
            + d->bottomTextMargin
            + d->topmargin
            + d->bottommargin;

    int w = fm.maxWidth()
            + d->leftTextMargin
            + d->rightTextMargin
            + d->leftmargin
            + d->rightmargin;

    QStyleOptionFrame opt;
    initStyleOption(&opt);
    return (style()->sizeFromContents(QStyle::CT_LineEdit, &opt,
        QSize(w, h).expandedTo(QApplication::globalStrut()), this));
}

void QsPasswordInput::setTextMargins(int left, int top, int right, int bottom)
{
    Q_D(QsPasswordInput);
    d->leftTextMargin = left;
    d->topTextMargin = top;
    d->rightTextMargin = right;
    d->bottomTextMargin = bottom;
    updateGeometry();
    update();
}

void QsPasswordInput::setTextMargins(const QMargins &margins)
{
    setTextMargins(margins.left(), margins.top(), margins.right(), margins.bottom());
}

void QsPasswordInput::getTextMargins(int *left, int *top, int *right, int *bottom) const
{
    Q_D(const QsPasswordInput);
    if (left)   *left = d->leftTextMargin;
    if (top)    *top = d->topTextMargin;
    if (right)  *right = d->rightTextMargin;
    if (bottom) *bottom = d->bottomTextMargin;
}

QMargins QsPasswordInput::textMargins() const
{
    Q_D(const QsPasswordInput);
    return QMargins(d->leftTextMargin, d->topTextMargin, d->rightTextMargin, d->bottomTextMargin);
}

bool QsPasswordInput::event(QEvent * e)
{
    return QWidget::event(e);
//    std::cout << "event " << std::endl;
}

void QsPasswordInput::mousePressEvent(QMouseEvent* e)
{
//    std::cout << "mousePressEvent " << std::endl;
    Q_D(QsPasswordInput);
    if (e->button() == Qt::RightButton)
        return;
     e->accept();
     update();
}

void QsPasswordInput::mouseMoveEvent(QMouseEvent * e)
{
//    std::cout << "mouseMoveEvent " << std::endl;
//    Q_D(QsPasswordInput);
    e->ignore();
}

void QsPasswordInput::mouseReleaseEvent(QMouseEvent* e)
{
//    std::cout << "mouseReleaseEvent " << std::endl;
//    Q_D(QsPasswordInput);
    e->ignore();
}

void QsPasswordInput::mouseDoubleClickEvent(QMouseEvent* e)
{
//    std::cout << "mouseDoubleClickEvent " << std::endl;
//    Q_D(QsPasswordInput);
//    if (e->button() == Qt::LeftButton) {
//        e->accept();
//    } else {
//    }
    e->ignore();
}

//
//  ctrl X - delete all
//  ctrl S - show/hide
//  ctrl V - paste from clipboard
//  backspace - delete left
//  del - delete left
//

void QsPasswordInput::keyPressEvent(QKeyEvent *e)
{
    auto kMods = QGuiApplication::keyboardModifiers();
    auto key = e->key();
    auto controlKeys = kMods & Qt::ControlModifier;
    Q_D(QsPasswordInput);

    if(controlKeys) {
        switch( key ) {
        // clear password
        case Qt::Key_X:
            d->password.clear();
            d->showPassword = false;
            emit textChanged();
            break;

        // show/hide password
        case Qt::Key_S:
            d->showPassword = d->password.size() > 0 ? ! d->showPassword : false;
            break;

        // paste password from clipboard
        case Qt::Key_V:
            if( ! d->clipboardEnabled ) {
                e->ignore();
                return;
            }
            if( clipboardPaste( d->password )) {
                d->showPassword = false;
                emit textChanged();
            }
            break;

        default:
            e->ignore();
            return;
        }
    } else {
        switch( key ) {

        // delete left
        case Qt::Key_Delete:
        case Qt::Key_Backspace:
            if( d->password.size() > 0 ) {
                d->password.trimLastUtf8();
                emit textChanged();
            }
            if( d->password.size() == 0 ) {
                d->showPassword = false;
            }
            break;

        // ready
        case Qt::Key_Enter:
        case Qt::Key_Return:
            d->showPassword = false;
            emit returnPressed();
            break;

        default:
            // get text and add to password
            const QString str = e->text(); // will be shared
            if( str.length() == 0 ) {
                e->ignore();
                return;
            }
            {
                // may not be neccessary if composition not enabled
                const QString normalized( str.normalized( d->normalizationForm, QChar::Unicode_8_0 ));  // will be shared
                const QByteArray utf8val( normalized.toUtf8() );  // will be shared
                utf8string::size_type utf8len = utf8val.size();
                utf8string::size_type pwLen = d->password.size();
                // TODO: refine length check -- character count check : too long, too short
                if( d->maxLength >= (utf8len+pwLen) ) {
                    d->password.insert(std::end(d->password), std::begin(utf8val), std::end(utf8val));
                } else {
                    emit passwordTooLong();
                }                
                secureClear(utf8val);
                secureClear(normalized);
                emit textChanged();
            }
            secureClear(str);
        }
    }
    e->accept();
    update();
}

// not implemented
void QsPasswordInput::inputMethodEvent(QInputMethodEvent *e)
{
    Q_D(QsPasswordInput);
    d->processInputMethodEvent(e);
}

void QsPasswordInput::focusInEvent(QFocusEvent *e)
{
//    std::cout << "focusInEvent " << std::endl;
    QWidget::focusInEvent(e);
}


void QsPasswordInput::focusOutEvent(QFocusEvent *e)
{
//    std::cout << "focusOutEvent " << std::endl;
    QWidget::focusOutEvent(e);
}

void QsPasswordInput::changeEvent(QEvent *e)
{
//    std::cout << "changeEvent " << std::endl;
//    Q_D(QsPasswordInput);
//    switch(e->type())
//    {
//    case QEvent::FontChange:
//        break;
//    default:
//        break;
//    }
//    QWidget::changeEvent(e);
    e->ignore();
}

// with breeze there is no frame with fusion is ok

void QsPasswordInput::paintEvent(QPaintEvent *e)
{
    Q_D(QsPasswordInput);
    auto pwlen = d->password.charCount();
    QString displayText( pwlen, d->hideCharacter );
    if( d->showPassword && ( d->password.size() > 0 )) {
        displayText = QString::fromUtf8( d->password.data(),  d->password.size() );
    }

    QPainter p(this);
    QPalette pal = palette();
    QStyleOptionFrame panel;
    initStyleOption(&panel);

    style()->drawPrimitive( QStyle::PE_PanelLineEdit, &panel, &p, this );
    QRect textRect = style()->subElementRect( QStyle::SE_LineEditContents, &panel, this );
    textRect.adjust( d->leftTextMargin, d->topTextMargin, -d->rightTextMargin, -d->bottomTextMargin );

// cannot link
//    if (QStyleSheetStyle* cssStyle = qobject_cast<QStyleSheetStyle*>(style())) {
//        cssStyle->styleSheetPalette(this, &panel, &pal);
//    }

    p.setClipRect(textRect);
    QFontMetrics fm = fontMetrics();
    int pixelsWide = fm.width(displayText);
    int textAlign = Qt::AlignLeft | Qt::AlignVCenter;
    if( pixelsWide >= textRect.width() ) {
        textAlign = Qt::AlignRight | Qt::AlignVCenter;
    }
    style()->drawItemText( &p, textRect, textAlign, pal, true, displayText, QPalette::Text );
    secureClear(displayText);
}


QT_END_NAMESPACE

