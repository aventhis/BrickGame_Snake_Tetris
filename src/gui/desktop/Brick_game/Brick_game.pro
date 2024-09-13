QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../../brick_game/snake/snake_fsm.cpp \
    ../../../brick_game/snake/snake_game_model.cpp \
    ../../../brick_game/tetris/fsm.c \
    ../../../brick_game/tetris/game_logic.c \
    gameboard.cpp \
    gamechooser.cpp \
    gamewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    snakeboard.cpp \
    snakewindow.cpp \
    tetrixboard.cpp \
    tetrixwindow.cpp

HEADERS += \
    ../../../brick_game/sharedfunction.h \
    ../../../brick_game/snake/snake_game_model.h \
    ../../../brick_game/tetris/game_logic.h \
    ../../cli/snake/snake_game_view.h \
    gameboard.h \
    gamechooser.h \
    gamewindow.h \
    mainwindow.h \
    snakeboard.h \
    snakewindow.h \
    tetrixboard.h \
    tetrixwindow.h

LIBS += -lncurses

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
