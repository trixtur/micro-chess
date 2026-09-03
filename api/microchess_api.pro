TEMPLATE = app
QT += core network
CONFIG += console c++17
CONFIG -= app_bundle

INCLUDEPATH += ../src
SOURCES += main.cpp ../src/game_api.cpp \
           ../src/board.cpp ../src/pieces.cpp ../src/pawn.cpp \
           ../src/rook.cpp ../src/knight.cpp ../src/queen.cpp ../src/king.cpp
