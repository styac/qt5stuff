# to make the test

QT += core gui widgets

TARGET = qywidgets_test
TEMPLATE = app

#CONF = release
CONF = debug

include( qywidgets.pri )

SOURCES += \
    test/MainWindow.cpp \
    test/main.cpp

HEADERS += \
    test/MainWindow.h

FORMS += \
    test/MainWindow.ui
