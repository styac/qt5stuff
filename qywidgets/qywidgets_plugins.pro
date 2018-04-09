# to make plugin for designer

# dir: /usr/lib64/qt5/plugins
# sudo cp /home/collection/sw/NetBeansProjects/qywidgets_build/release/libqywidgets_plugin.so /usr/lib64/qt5/plugins/designer/


QT  += widgets uiplugin designer
CONFIG  += plugin
TEMPLATE = lib
TARGET = qywidgets_plugin

CONF = release
# CONF = debug

include( qywidgets.pri )

SOURCES += \
    designer-plugin/QyController_plugin.cpp \
    designer-plugin/QyIndicator_plugin.cpp \
    designer-plugin/QyWidgetCollection.cpp

HEADERS += \
    designer-plugin/QyController_plugin.h \
    designer-plugin/QyIndicator_plugin.h \
    designer-plugin/QyWidgetCollection.h

