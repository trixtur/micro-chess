TEMPLATE = app
QT += core
CONFIG += console c++17
CONFIG -= app_bundle

INCLUDEPATH += ../src
SOURCES += main.cpp \
           ../src/board.cpp ../src/pieces.cpp ../src/pawn.cpp \
           ../src/rook.cpp ../src/knight.cpp ../src/queen.cpp ../src/king.cpp
