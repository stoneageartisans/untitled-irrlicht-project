#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug-Linux
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/source/application.o \
	${OBJECTDIR}/source/character.o \
	${OBJECTDIR}/source/database.o \
	${OBJECTDIR}/source/day.o \
	${OBJECTDIR}/source/main.o \
	${OBJECTDIR}/source/time.o \
	${OBJECTDIR}/source/ui.o \
	${OBJECTDIR}/source/user.o \
	${OBJECTDIR}/source/world.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../../libraries/irrlicht-1.8.3/lib/Linux -L../../../libraries/sqlite-3.8.4.2/lib/Linux64 -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lsqlite

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk debug-linux

debug-linux: ${OBJECTFILES}
	${LINK.cc} -o debug-linux ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/source/application.o: source/application.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_IRR_STATIC_LIB_ -I../../../libraries/irrlicht-1.8.3/include -I../../../libraries/sqlite-3.8.4.2/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/application.o source/application.cpp

${OBJECTDIR}/source/character.o: source/character.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_IRR_STATIC_LIB_ -I../../../libraries/irrlicht-1.8.3/include -I../../../libraries/sqlite-3.8.4.2/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/character.o source/character.cpp

${OBJECTDIR}/source/database.o: source/database.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_IRR_STATIC_LIB_ -I../../../libraries/irrlicht-1.8.3/include -I../../../libraries/sqlite-3.8.4.2/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/database.o source/database.cpp

${OBJECTDIR}/source/day.o: source/day.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_IRR_STATIC_LIB_ -I../../../libraries/irrlicht-1.8.3/include -I../../../libraries/sqlite-3.8.4.2/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/day.o source/day.cpp

${OBJECTDIR}/source/main.o: source/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_IRR_STATIC_LIB_ -I../../../libraries/irrlicht-1.8.3/include -I../../../libraries/sqlite-3.8.4.2/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/main.o source/main.cpp

${OBJECTDIR}/source/time.o: source/time.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_IRR_STATIC_LIB_ -I../../../libraries/irrlicht-1.8.3/include -I../../../libraries/sqlite-3.8.4.2/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/time.o source/time.cpp

${OBJECTDIR}/source/ui.o: source/ui.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_IRR_STATIC_LIB_ -I../../../libraries/irrlicht-1.8.3/include -I../../../libraries/sqlite-3.8.4.2/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/ui.o source/ui.cpp

${OBJECTDIR}/source/user.o: source/user.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_IRR_STATIC_LIB_ -I../../../libraries/irrlicht-1.8.3/include -I../../../libraries/sqlite-3.8.4.2/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/user.o source/user.cpp

${OBJECTDIR}/source/world.o: source/world.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_IRR_STATIC_LIB_ -I../../../libraries/irrlicht-1.8.3/include -I../../../libraries/sqlite-3.8.4.2/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/world.o source/world.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} debug-linux

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
