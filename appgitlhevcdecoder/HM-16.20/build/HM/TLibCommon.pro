# ----------------------------------------------------

# ------------------------------------------------------

TEMPLATE = lib
CONFIG(debug, debug|release){
    TARGET = TLibCommond
}
CONFIG(release, debug|release){
    TARGET = TLibCommon
}

CONFIG += staticlib
CONFIG += c++20
DEFINES += _CRT_SECURE_NO_WARNINGS
INCLUDEPATH += ../../source/Lib
DEPENDPATH += .
DESTDIR = $${OUT_PWD}/..
include(TLibCommon.pri)
