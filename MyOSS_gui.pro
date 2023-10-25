QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    objectlist.cpp \
    objecttablemodel.cpp \
    tasklist.cpp \
    tasktablemodel.cpp

HEADERS += \
    mainwindow.h \
    objectlist.h \
    objecttablemodel.h \
    tasklist.h \
    tasktablemodel.h

FORMS += \
    mainwindow.ui \
    objectlist.ui \
    tasklist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
