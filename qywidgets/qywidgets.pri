# include into each *pro
#CONF = release
#CONF = debug

CONFIG += $$CONF
DESTDIR = $$clean_path( $$PWD/../qywidgets_build/$$CONF )

OBJECTS_DIR = $${DESTDIR}/obj
MOC_DIR = $${DESTDIR}/moc
UI_DIR = $${DESTDIR}/uic
RCC_DIR = $${DESTDIR}/rcc

QMAKE_CXXFLAGS += -Wno-unused-variable -Wno-unused-parameter -Wno-switch
DEFINES += QT_DEPRECATED_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0x060000

CONFIG += c++14
QMAKE_CC = gcc-7
QMAKE_CXX = g++-7
QMAKE_CXXFLAGS_DEBUG += -O0
QMAKE_CXXFLAGS_RELEASE += -O2

# QT_PREF = /usr/local/qt5.9/include
# QT_VER = 5.9.4
# LIBS = -L/usr/local/qt5.9/lib

QT_PREF = /usr/include/qt5
QT_VER = 5.6.2

INCLUDEPATH += \
    /usr/include/c++/7 \
    /usr/include/c++/7/x86_64-suse-linux \
    /usr/lib64/gcc/x86_64-suse-linux/7/include \
    /usr/lib64/gcc/x86_64-suse-linux/7/include-fixed \
    $$QT_PREF/QtWidgets/$$QT_VER/ \
    $$QT_PREF/QtCore/$$QT_VER/ \
    $$QT_PREF/QtGui/$$QT_VER/ \
    $$QT_PREF/QtGui/$$QT_VER/QtGui \
    $$QT_PREF/QtWidgets/$$QT_VER/QtWidgets/ \
    $$QT_PREF/QtCore/$$QT_VER/QtCore \
    qywidgets/private \
    qywidgets/include

SOURCES += \
    qywidgets/src/QyMinimalSylePainter.cpp \
    qywidgets/src/QyStyleOption.cpp \
    qywidgets/src/QyAbstractController.cpp \
    qywidgets/src/QyAbstractIndicator.cpp \
    qywidgets/src/QyController.cpp \
    qywidgets/src/QyIndicator.cpp \
    qywidgets/src/QyColors.cpp \
    qywidgets/src/QyTransfomerParameters.cpp \
    qywidgets/src/QyValueTransfomer.cpp \
    qywidgets/src/QyClipboard.cpp

HEADERS += \
    qywidgets/private/QyController_p.h \
    qywidgets/private/QyStyleOption.h \
    qywidgets/private/QyAbstractController_p.h \
    qywidgets/private/QyAbstractIndicator_p.h \
    qywidgets/private/QyIndicator_p.h \
    qywidgets/private/QyColors.h \
    qywidgets/private/QyStyleData.h \
    qywidgets/private/QyValue.h \
    qywidgets/private/QyValueHandler.h \
    qywidgets/private/QyValueTransfomer.h \
    qywidgets/include/QyEnums.h \
    qywidgets/include/QyAbstractController.h \
    qywidgets/include/QyAbstractIndicator.h \
    qywidgets/include/QyController.h \
    qywidgets/include/QyIndicator.h \
    qywidgets/include/QyTypes.h \
    qywidgets/include/QyConsts.h \
    qywidgets/include/QyTransfomerParameters.h \
    qywidgets/include/QyGlobal.h \
    qywidgets/include/QyWidgetVector.h \
    qywidgets/include/QyClipboard.h

