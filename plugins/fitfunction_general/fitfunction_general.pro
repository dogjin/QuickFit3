TEMPLATE = lib
CONFIG += plugin

TARGET = fitfunction_general
DEPENDPATH += ./

include(../plugins.pri)
DESTDIR = $$QFOUTPUT/plugins

# Input
HEADERS += qfgeneralfitfunctionsplugin.h \
           qffitfunctiongeneralsigmoid.h \
    ../../../../../LIB/trunk/statistics_tools.h \
    qffitfunctiongeneralgaussianvar.h \
    qffitfunctiongenerallorentzian.h \
    qffitfunctiongeneralpowerlaw.h \
    qffitfunctiongeneralexp.h \
    qffitfunctiongeneraldblexp.h \
    qffitfunctiongeneralpolynom.h \
    qffitfunctiongeneralsine.h \
    qffitfunctiongenerallognormal.h \
    qffitfunctiongeneralline.h \
    qffitfunctiongeneral3gaussianvar.h \
    qffitfunctiongeneral2gaussianvar.h

SOURCES += qfgeneralfitfunctionsplugin.cpp\
           qffitfunctiongeneralsigmoid.cpp \
    ../../../../../LIB/trunk/statistics_tools.cpp \
    qffitfunctiongeneralgaussianvar.cpp \
    qffitfunctiongenerallorentzian.cpp \
    qffitfunctiongeneralpowerlaw.cpp \
    qffitfunctiongeneralexp.cpp \
    qffitfunctiongeneraldblexp.cpp \
    qffitfunctiongeneralsine.cpp \
    qffitfunctiongeneralpolynom.cpp \
    qffitfunctiongenerallognormal.cpp \
    qffitfunctiongeneralline.cpp \
    qffitfunctiongeneral3gaussianvar.cpp \
    qffitfunctiongeneral2gaussianvar.cpp

FORMS =

RESOURCES +=

TRANSLATIONS= ./translations/de.fitfunction_general.ts


INCLUDEPATH += ../../lib/


QT += core
CONFIG += exceptions rtti stl

SRC_DISTRIBUTED.files = $$HEADERS \
                        $$SOURCES \
                        $$FORMS \
                        $$RESOURCES \
                        $$TRANSLATIONS

