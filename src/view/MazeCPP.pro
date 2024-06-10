QT       += core gui widgets

CONFIG += c++17

SOURCES += \
    ../model/cave.cc \
    ../model/maze.cc \
    ../model/pathfinder.cc \
    caveview.cc \
    cavewindow.cc \
    main.cc \
    mainwindow.cc \
    mazeview.cc

HEADERS += \
    ../controller/controller.h \
    ../model/cave.h \
    ../model/maze.h \
    ../model/pathfinder.h \
    caveview.h \
    cavewindow.h \
    mainwindow.h \
    mazeview.h

FORMS += \
    cavewindow.ui \
    mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
