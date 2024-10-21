QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Application/Application.cpp \
    ../Application/Array.cpp \
    ../Application/Complex.cpp \
    ../Application/Polynom.cpp \
    Array.cpp \
    Complex.cpp \
    Polynom.cpp \
    interface.cpp \
    main.cpp

HEADERS += \
    ../Application/Application.h \
    ../Application/Array.h \
    ../Application/Complex.h \
    ../Application/Polynom.h \
    ../Application/enums.h \
    ../Application/number.h \
    Array.h \
    Complex.h \
    Polynom.h \
    enums.h \
    interface.h \
    number.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
