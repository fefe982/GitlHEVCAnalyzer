# ----------------------------------------------------

# ------------------------------------------------------


TEMPLATE = lib
CONFIG(debug, debug|release){
    TARGET = TAppCommond
}
CONFIG(release, debug|release){
    TARGET = TAppCommon
}
CONFIG += staticlib
CONFIG += c++20
DEFINES += _CRT_SECURE_NO_WARNINGS
INCLUDEPATH += ../../source/Lib
DEPENDPATH += .
DESTDIR = $${OUT_PWD}/..
include(TAppCommon.pri)
