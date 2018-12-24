# to make static lib

QT += widgets

TARGET = qswidgets
TEMPLATE = lib
CONFIG += staticlib

# include into each *pro
CONF = release
#CONF = debug

include( qswidgets.pri )

