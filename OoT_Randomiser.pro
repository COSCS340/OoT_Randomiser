#-------------------------------------------------
#
# Project created by QtCreator 2018-02-25T16:24:46
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OoT_Randomiser
TEMPLATE = app

CONFIG += debug

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Force security hardening
QMAKE_CXXFLAGS_RELEASE += _FORTIFY_SOURCE=2

CONFIG(linux*|*BSD*) {
  QMAKE_CXXFLAGS += -fstack-protector-strong
}
CONFIG(!windows) {
QMAKE_CXX = g++ -fsantize=address -fsanitize=undefined
CONFIG(mac) {
QMAKE_CXX = clang++ -fsanitize=undefined -fsanitize-trap-on-error
}
QMAKE_CXXFLAGS += -std=c++17 -g3 -v
}
SOURCES += \
    colors/color_driver.cpp \
    Common/game.cpp \
    GUI/main.cpp \
    GUI/mainwindow.cpp \
    GUI/offthreadrandomizer.cpp \
    Randomiser/randomizer.cpp \
    Decoder/decoder.cpp \
    Decoder/crc.c

HEADERS += \
    colors/custom_colors.h \
    Common/game.hpp \
    Extractor/extract.hpp \
    GUI/mainwindow.h \
    GUI/offthreadrandomizer.h \
    Randomiser/args.h \
    Randomiser/chests.h \
    Randomiser/custom_colors.h \
    Randomiser/items.h \
    Decoder/crc.h \
    Decoder/decoder.hpp

FORMS += \
    GUI/mainwindow.ui

DISTFILES += \
    Temp/locations.txt
