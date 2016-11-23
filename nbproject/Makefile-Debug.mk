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
CND_PLATFORM=mingw-w64-64-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/TrackinDevice.o \
	${OBJECTDIR}/src/collections/SList.o \
	${OBJECTDIR}/src/rtracker.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../slog/dist/Debug/mingw-w64-64-Windows/libslog.a ../ccollections/dist/Debug/mingw-w64-64-Windows/libccollections.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rtracker.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rtracker.exe: ../slog/dist/Debug/mingw-w64-64-Windows/libslog.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rtracker.exe: ../ccollections/dist/Debug/mingw-w64-64-Windows/libccollections.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rtracker.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rtracker ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/TrackinDevice.o: src/TrackinDevice.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -I../slog/include -I../ccollections/include -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/TrackinDevice.o src/TrackinDevice.c

${OBJECTDIR}/src/collections/SList.o: src/collections/SList.c 
	${MKDIR} -p ${OBJECTDIR}/src/collections
	${RM} "$@.d"
	$(COMPILE.c) -g -I../slog/include -I../ccollections/include -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/collections/SList.o src/collections/SList.c

${OBJECTDIR}/src/rtracker.o: src/rtracker.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -I../slog/include -I../ccollections/include -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/rtracker.o src/rtracker.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rtracker.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
