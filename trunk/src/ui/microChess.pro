HEADERS     = microChess.h 
SOURCES	    = microChess.cpp main.cpp
FORMS       = microChess.ui

# install
target.path = microChess
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS *.pro
sources.path = .
INSTALLS += target sources


