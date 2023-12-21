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
    gameaddingwindow.cpp \
    gamesdbmanager.cpp \
    gamewindow.cpp \
    main.cpp \
    entrywindow.cpp \
    profilewindow.cpp \
    purchasedgamesdbmanager.cpp \
    registrationwindow.cpp \
    sqlitedbmanager.cpp \
    user.cpp \
    usersdbmanager.cpp

HEADERS += \
    Config.h \
    DBManager.h \
    Enums.h \
    GameCard.h \
    browsewindow.h \
    entrywindow.h \
    game.h \
    gameaddingwindow.h \
    gamesdbmanager.h \
    gamewindow.h \
    profilewindow.h \
    purchasedgamesdbmanager.h \
    registrationwindow.h \
    sqlitedbmanager.h \
    user.h \
    usersdbmanager.h

FORMS += \
    browsewindow.ui \
    entrywindow.ui \
    gameaddingwindow.ui \
    gamewindow.ui \
    profilewindow.ui \
    registrationwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
