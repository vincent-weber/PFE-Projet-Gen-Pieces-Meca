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
LIBS += -L$(HOME)/lib/CGAL-5.2/lib -lgmp -lmpfr

SOURCES += main.cpp\
        boolean_op.cpp \
        cuboid.cpp \
        cylinder.cpp \
        generator.cpp \
        mechanicalpart.cpp \
        parser.cpp \
        princ.cpp \
        glarea.cpp \
        screwgenerator.cpp \
        shape3d.cpp \
        sphere.cpp \
        util.cpp

HEADERS  += princ.h \
        Cgal.h \
        boolean_op.h \
        cuboid.h \
        cylinder.h \
        generator.h \
        glarea.h \
        mechanicalpart.h \
        parser.h \
        screwgenerator.h \
        shape3d.h \
        sphere.h \
        util.h

FORMS    += princ.ui

RESOURCES += \
    gen_pieces_meca.qrc
