#-------------------------------------------------
#
# Project created by QtCreator 2018-10-19T22:30:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projet-advance
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    gameobject.cpp \
    game.cpp \
    map.cpp \
    terrain.cpp \
    mountain.cpp \
    plain.cpp \
    lake.cpp \
    unite.cpp \
    infantry.cpp \
    recon.cpp \
    mech.cpp \
    antiair.cpp \
    tank.cpp \
    mdtank.cpp \
    megatank.cpp \
    neotank.cpp \
    bcopter.cpp \
    fighter.cpp \
    bomber.cpp \
    building.cpp \
    airport.cpp \
    base.cpp \
    city.cpp \
    wood.cpp \
    river.cpp \
    road.cpp \
    bridge.cpp \
    shoal.cpp \
    reef.cpp \
    pipe.cpp \
    dialogunitprice.cpp \
    dialogbuyterre.cpp \
    dialogbuyair.cpp \
    dialogshowrules.cpp \
    dialogshowcommands.cpp \
    dialoglanguage.cpp \
    introwindow.cpp \

HEADERS += \
        mainwindow.h \
    gameobject.h \
    game.h \
    map.h \
    terrain.h \
    mountain.h \
    plain.h \
    lake.h \
    unite.h \
    infantry.h \
    recon.h \
    mech.h \
    antiair.h \
    tank.h \
    mdtank.h \
    megatank.h \
    neotank.h \
    bcopter.h \
    fighter.h \
    bomber.h \
    building.h \
    airport.h \
    base.h \
    city.h \
    wood.h \
    river.h \
    road.h \
    bridge.h \
    shoal.h \
    reef.h \
    pipe.h \
    dialogunitprice.h \
    dialogbuyterre.h \
    dialogbuyair.h \
    dialogshowrules.h \
    dialogshowcommands.h \
    dialoglanguage.h \
    introwindow.h \

FORMS += \
        mainwindow.ui \
    dialogunitprice.ui \
    dialogbuyterre.ui \
    dialogbuyair.ui \
    dialogshowrules.ui \
    dialogshowcommands.ui \
    dialoglanguage.ui \
    introwindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \

