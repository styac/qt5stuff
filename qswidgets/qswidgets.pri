# include into each *pro
#CONF = release
#CONF = debug

CONFIG += $$CONF
DESTDIR = $$clean_path( $$PWD/../qswidgets_build/$$CONF )

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

QT_PREF = /usr/include/qt5
#QT_PREF = /usr/local/qt5.9/include
QT_VER = 5.9.4

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
    qspasswordinput/private \
    qspasswordinput/include

SOURCES += \
    qspasswordinput/src/QsPasswordInput.cpp

HEADERS += \
    qspasswordinput/private/QsPasswordInput_p.h \
    qspasswordinput/include/QsPasswordInput.h \
    qspasswordinput/include/QsGlobal.h \
    qspasswordinput/include/secureclear.h \
    qspasswordinput/include/pwstring.h



