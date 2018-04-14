# to make static lib


QT += widgets

TARGET = qywidgets
TEMPLATE = lib
CONFIG += staticlib

# include into each *pro
#CONF = release
CONF = debug

include( qywidgets.pri )

