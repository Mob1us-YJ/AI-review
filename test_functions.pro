QT += core
QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

TEMPLATE = app

TARGET = test_functions

SOURCES += \
    test_functions.cpp \
    scanmanager.cpp \
    printmanager.cpp \
    networkmanager.cpp \
    exammanager.cpp

HEADERS += \
    scanmanager.h \
    printmanager.h \
    networkmanager.h \
    exammanager.h

# 默认规则用于部署
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target 