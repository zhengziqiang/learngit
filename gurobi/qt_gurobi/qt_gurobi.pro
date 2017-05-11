QT += core
QT -= gui

CONFIG += c++11

TARGET = qt_gurobi
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    sub.cpp \
    test.cpp

#LIBS+=-L/home/zzq/gurobi702/linux64/lib/ -lgurobi_c++ -lgurobi70 -lm
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


#extraclean.commands=g++ -m64 -g -o gurobi.cpp /home/zzq/qt_gurobi/gurobi.cpp -I/home/zzq/gurobi702/linux64/include/ -L

#distclean.depends = extraclean
#QMAKE_EXTRA_TARGETS += distclean extraclean


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
# disables all the APIs deprecated before Qt 6.0.0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../gurobi702/linux64/lib/release/ -laes70
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../gurobi702/linux64/lib/debug/ -laes70
else:unix: LIBS += -L$$PWD/../gurobi702/linux64/lib/ -laes70

INCLUDEPATH += $$PWD/../gurobi702/linux64/include
DEPENDPATH += $$PWD/../gurobi702/linux64/include

unix:!macx: LIBS += -L$$PWD/../gurobi702/linux64/lib/ -lgurobi_g++4.1

INCLUDEPATH += $$PWD/../gurobi702/linux64/include
DEPENDPATH += $$PWD/../gurobi702/linux64/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../gurobi702/linux64/lib/libgurobi_g++4.1.a

unix:!macx: LIBS += -L$$PWD/../gurobi702/linux64/lib/ -lgurobi70

INCLUDEPATH += $$PWD/../gurobi702/linux64/include
DEPENDPATH += $$PWD/../gurobi702/linux64/include
