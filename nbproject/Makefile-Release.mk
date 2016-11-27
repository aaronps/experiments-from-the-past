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
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/iterations.o \
	${OBJECTDIR}/src/sfsigslot.o \
	${OBJECTDIR}/src/virtualcall.o \
	${OBJECTDIR}/src/Test_Boost.o \
	${OBJECTDIR}/src/Test_FastDelegate.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-mcpu=core2 -O4
CXXFLAGS=-mcpu=core2 -O4

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppcall

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppcall: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -lboost_signals -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppcall ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/iterations.o: iterations.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -MMD -MP -MF $@.d -o ${OBJECTDIR}/iterations.o iterations.cpp

${OBJECTDIR}/src/sfsigslot.o: src/sfsigslot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sfsigslot.o src/sfsigslot.cpp

${OBJECTDIR}/src/virtualcall.o: src/virtualcall.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/virtualcall.o src/virtualcall.cpp

${OBJECTDIR}/src/Test_Boost.o: src/Test_Boost.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Test_Boost.o src/Test_Boost.cpp

${OBJECTDIR}/src/Test_FastDelegate.o: src/Test_FastDelegate.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Test_FastDelegate.o src/Test_FastDelegate.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppcall

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
