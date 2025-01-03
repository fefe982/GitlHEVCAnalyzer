# ----------------------------------------------------

# ------------------------------------------------------

TEMPLATE = subdirs
CONFIG += ordered
CONFIG += c++20
SUBDIRS += \
    HM/TAppCommon.pro \
    HM/TLibCommon.pro \
    HM/TLibDecoder.pro \
    HM/TLibVideoIO.pro \
    HM/TLibSysuAnalyzer.pro\
    HM/TAppDecoder.pro
