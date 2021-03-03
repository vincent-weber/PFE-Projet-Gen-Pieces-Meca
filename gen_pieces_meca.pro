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
        anchorpoint.cpp \
        boolean_op.cpp \
        box.cpp \
        cuboid.cpp \
        cylinder.cpp \
        engine.cpp \
        generator.cpp \
        machinery.cpp \
        mechanicalpart.cpp \
        nut.cpp \
        parser.cpp \
        pipe.cpp \
        piston.cpp \
        primitive.cpp \
        princ.cpp \
        glarea.cpp \
        screw.cpp \
        sphere.cpp \
        util.cpp

HEADERS  += princ.h \
        Cgal.h \
        anchorpoint.h \
        boolean_op.h \
        box.h \
        cuboid.h \
        cylinder.h \
        engine.h \
        generator.h \
        glarea.h \
        machinery.h \
        mechanicalpart.h \
        nut.h \
        parser.h \
        pipe.h \
        piston.h \
        primitive.h \
        screw.h \
        sphere.h \
        util.h

FORMS    += princ.ui

RESOURCES += \
    gen_pieces_meca.qrc
