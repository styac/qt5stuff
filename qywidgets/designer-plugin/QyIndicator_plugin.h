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

#include <QObject>
// #include <QDesignerCustomWidgetInterface>
#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class QyIndicator_plugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
    //Q_PLUGIN_METADATA(IID "com.ics.Qt.CustomWidgets")

public:
    explicit QyIndicator_plugin(QObject *parent = nullptr);

    void initialize(QDesignerFormEditorInterface *core) Q_DECL_OVERRIDE;
    bool isInitialized() const Q_DECL_OVERRIDE;

    QWidget *createWidget(QWidget *parent) Q_DECL_OVERRIDE;

    QString name() const Q_DECL_OVERRIDE;
    QString group() const Q_DECL_OVERRIDE;
    QIcon icon() const Q_DECL_OVERRIDE;
    QString toolTip() const Q_DECL_OVERRIDE;
    QString whatsThis() const Q_DECL_OVERRIDE;
    bool isContainer() const Q_DECL_OVERRIDE;

    QString domXml() const Q_DECL_OVERRIDE;

    QString includeFile() const Q_DECL_OVERRIDE;

private:
    bool initialized;
};

