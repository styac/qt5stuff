# to make the test

QT += core gui widgets

TARGET = qswidgets_test
TEMPLATE = app

#CONF = release
CONF = debug

include( qswidgets.pri )

SOURCES += \
    test/MainWindow.cpp \
    test/main.cpp

HEADERS += \
    test/MainWindow.h

FORMS += \
    test/MainWindow.ui


