QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GameCard.cpp \
    browsewindow.cpp \
    game.cpp \
    gamesdbmanager.cpp \
    gamewindow.cpp \
    main.cpp \
    entrywindow.cpp \
    mysqldbmanager.cpp \
    profilewindow.cpp \
    user.cpp

HEADERS += \
    Config.h \
    DBManager.h \
    Enums.h \
    GameCard.h \
    browsewindow.h \
    entrywindow.h \
    game.h \
    gamesdbmanager.h \
    gamewindow.h \
    mysqldbmanager.h \
    profilewindow.h \
    user.h

FORMS += \
    browsewindow.ui \
    entrywindow.ui \
    gamewindow.ui \
    profilewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
