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

// collection of widgets
// https://techbase.kde.org/Development/Tutorials/Writing_Qt_Designer_Plugins


// 1 #ifndef MYWIDGETDESIGNERFACTORYCOLLECTION_H
// 2 #define MYWIDGETDESIGNERFACTORYCOLLECTION_H
// 3
// 4 // Qt
// 5 #include <QtDesigner/QDesignerCustomWidgetCollectionInterface>
// 6 #include <QtCore/QObject>
// 7
// 8 class MyWidgetDesignerFactoryCollection : public QObject, public QDesignerCustomWidgetCollectionInterface
// 9 {
//10   Q_OBJECT
//11   Q_INTERFACES( QDesignerCustomWidgetCollectionInterface
//12
//13   public:
//14     explicit MyWidgetDesignerFactoryCollection( QObject* parent = 0 );
//15
//16   public: // QDesignerCustomWidgetCollectionInterface API
//17     virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;
//18
//19   private:
//20     QList<QDesignerCustomWidgetInterface*> mWidgetFactories;
//21 };
//22
//23 #endif


// 1 #include "mywidgetdesignerfactorycollection.h"
// 2
// 3 // plugin
// 4 #include "mywidgetdesignerfactory.h"
// 5 #include "myotherwidgetdesignerfactory.h"
// 6 // Qt
// 7 #include <QtCore/QtPlugin>
// 8
// 9 MyWidgetDesignerFactoryCollection::MyWidgetDesignerFactoryCollection( QObject* parent )
//10   : QObject( parent )
//11 {
//12      mWidgetFactories.append( new MyWidgetDesignerFactory(this) );
//13      mWidgetFactories.append( new MyOtherWidgetDesignerFactory(this) );
//14 }
//15
//16 QList<QDesignerCustomWidgetInterface*> MyWidgetDesignerFactoryCollection::customWidgets() const
//17 {
//18     return mWidgetFactories;
//19 }
//20
//21 Q_EXPORT_PLUGIN2( mydesignerplugin, MyWidgetDesignerFactoryCollection )


#include <QObject>
#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class QyIndicator_plugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
    // Q_PLUGIN_METADATA(IID "org.Qy.Qt.QyIndicatorInterface")

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


