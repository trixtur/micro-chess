#
# Gererated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Release/GNU-MacOSX

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/king.o \
	${OBJECTDIR}/src/rook.o \
	${OBJECTDIR}/src/ChessDriver.o \
	${OBJECTDIR}/src/queen.o \
	${OBJECTDIR}/src/pawn.o \
	${OBJECTDIR}/src/bishop.o \
	${OBJECTDIR}/src/pieces.o \
	${OBJECTDIR}/src/board.o \
	${OBJECTDIR}/src/knight.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} dist/Release/GNU-MacOSX/libmicrochess.a

dist/Release/GNU-MacOSX/libmicrochess.a: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-MacOSX
	${RM} dist/Release/GNU-MacOSX/libmicrochess.a
	${AR} rv dist/Release/GNU-MacOSX/libmicrochess.a ${OBJECTFILES} 
	$(RANLIB) dist/Release/GNU-MacOSX/libmicrochess.a

${OBJECTDIR}/src/king.o: src/king.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/king.o src/king.cpp

${OBJECTDIR}/src/rook.o: src/rook.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/rook.o src/rook.cpp

${OBJECTDIR}/src/ChessDriver.o: src/ChessDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/ChessDriver.o src/ChessDriver.cpp

${OBJECTDIR}/src/queen.o: src/queen.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/queen.o src/queen.cpp

${OBJECTDIR}/src/pawn.o: src/pawn.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/pawn.o src/pawn.cpp

${OBJECTDIR}/src/bishop.o: src/bishop.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/bishop.o src/bishop.cpp

${OBJECTDIR}/src/pieces.o: src/pieces.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/pieces.o src/pieces.cpp

${OBJECTDIR}/src/board.o: src/board.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/board.o src/board.cpp

${OBJECTDIR}/src/knight.o: src/knight.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/knight.o src/knight.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/GNU-MacOSX/libmicrochess.a

# Subprojects
.clean-subprojects:
