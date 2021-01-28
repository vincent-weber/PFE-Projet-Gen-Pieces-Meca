#-------------------------------------------------
#
# Project created by QtCreator 2019-01-12T12:27:11
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gen_pieces_meca
TEMPLATE = app

#Chemin CGAL
INCLUDEPATH += $(HOME)/lib/CGAL-5.2/include

SOURCES += main.cpp\
        cuboid.cpp \
        cylinder.cpp \
        princ.cpp \
        glarea.cpp \
        shape3d.cpp \
        sphere.cpp \
        util.cpp

HEADERS  += princ.h \
        Cgal.h \
        cuboid.h \
        cylinder.h \
        glarea.h \
        shape3d.h \
        sphere.h \
        util.h

FORMS    += princ.ui

RESOURCES += \
    gen_pieces_meca.qrc
