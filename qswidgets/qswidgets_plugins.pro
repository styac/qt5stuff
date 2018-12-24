# to make plugin for designer

# dir: /usr/lib64/qt5/plugins
# sudo cp qswidgets_build/release/libqswidgets_plugin.so /usr/lib64/qt5/plugins/designer/


QT  += widgets uiplugin designer
CONFIG  += plugin
TEMPLATE = lib
TARGET = qswidgets_plugin

CONF = release
# CONF = debug

include( qswidgets.pri )

SOURCES += \
    designer-plugin/QsPasswordInput_plugin.cpp

HEADERS += \
    designer-plugin/QsPasswordInput_plugin.h

