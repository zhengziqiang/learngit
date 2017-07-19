QT += core
QT -= gui

CONFIG += c++11

TARGET = convolution
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    conv.cpp \
    utili.cpp
INCLUDEPATH +=/usr/local/include/opencv2

LIBS+=

unix:!macx: LIBS += -L$$PWD/../../../opencv-2.4/build/lib/ -lopencv_core

INCLUDEPATH += $$PWD/../../../opencv-2.4/build/include
DEPENDPATH += $$PWD/../../../opencv-2.4/build/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lopencv_core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lopencv_core
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lopencv_core

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

unix:!macx: LIBS += -L$$PWD/../../../opencv-2.4/build/lib/ -lopencv_core

INCLUDEPATH += $$PWD/../../../opencv-2.4/build/lib
DEPENDPATH += $$PWD/../../../opencv-2.4/build/lib
