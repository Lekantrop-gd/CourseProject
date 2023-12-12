QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GameCard.cpp \
    browsewindow.cpp \
    cardcreator.cpp \
    game.cpp \
    gamewindow.cpp \
    main.cpp \
    entrywindow.cpp \
    profilewindow.cpp \
    user.cpp

HEADERS += \
    Config.h \
    Enums.h \
    GameCard.h \
    browsewindow.h \
    cardcreator.h \
    entrywindow.h \
    game.h \
    gamewindow.h \
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
