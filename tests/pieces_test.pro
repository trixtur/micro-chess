TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

INCLUDEPATH += ../src
SOURCES += pieces_test.cpp \
           ../src/pieces.cpp ../src/pawn.cpp ../src/rook.cpp \
           ../src/knight.cpp ../src/queen.cpp ../src/king.cpp
