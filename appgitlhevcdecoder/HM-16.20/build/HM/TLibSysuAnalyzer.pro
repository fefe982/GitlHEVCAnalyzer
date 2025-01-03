# ----------------------------------------------------

# ------------------------------------------------------

TEMPLATE = lib
CONFIG(debug, debug|release){
    TARGET = TLibSysuAnalyzerd
}
CONFIG(release, debug|release){
    TARGET = TLibSysuAnalyzer
}
CONFIG += staticlib
CONFIG += c++20
DEFINES += _CRT_SECURE_NO_WARNINGS
INCLUDEPATH += ../../source/Lib \
    ../../../TLibSysuAnalyzer
DEPENDPATH += .
DESTDIR = $${OUT_PWD}/..
include(TLibSysuAnalyzer.pri)
