QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addtoreceived.cpp \
    addtowaste.cpp \
    addtoworkers.cpp \
    are_u_sure.cpp \
    edit_window.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    addtoreceived.h \
    addtowaste.h \
    addtoworkers.h \
    are_u_sure.h \
    edit_window.h \
    login.h \
    mainwindow.h

FORMS += \
    addtoreceived.ui \
    addtowaste.ui \
    addtoworkers.ui \
    are_u_sure.ui \
    edit_window.ui \
    login.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
