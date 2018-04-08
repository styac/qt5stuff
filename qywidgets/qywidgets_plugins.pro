# to make plugin for designer


QT  += widgets uiplugin designer
CONFIG  += plugin
TEMPLATE = lib
TARGET = qywidgets_plugin

CONF = release
# CONF = debug

include( qywidgets.pri )

SOURCES += \
    designer-plugin/QyController_plugin.cpp \
    designer-plugin/QyIndicator_plugin.cpp

HEADERS += \
    designer-plugin/QyController_plugin.h \
    designer-plugin/QyIndicator_plugin.h

# CONFIG += debug
# CONFIG += release

