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
    designer-plugin/QyIndicator_plugin.cpp

HEADERS += \
    designer-plugin/QyController_plugin.h \
    designer-plugin/QyIndicator_plugin.h

# CONFIG += debug
# CONFIG += release

# https://www.ics.com/blog/integrating-custom-widget-qt-designer
# https://github.com/set-soft/led-designer-plugin
# https://github.com/creedr/QtPropertyBrowser/tree/master/plugin
# http://doc.qt.io/qt-5/designer-creating-custom-widgets.html
# https://github.com/mbasaglia/Qt-Color-Widgets/tree/master/color_widgets_designer_plugin
#
