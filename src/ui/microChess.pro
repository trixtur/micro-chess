QT += widgets
CONFIG += c++17

HEADERS = microChess.h ../board.h ../pieces.h ../common.h
SOURCES = microChess.cpp main.cpp ../board.cpp \
          ../pieces.cpp ../pawn.cpp ../rook.cpp ../knight.cpp ../queen.cpp ../king.cpp
FORMS = microChess.ui

# install
target.path = microChess
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS *.pro
sources.path = .
INSTALLS += target sources
