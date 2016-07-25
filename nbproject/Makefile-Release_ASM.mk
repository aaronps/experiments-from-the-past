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
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release_ASM
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/552806006/SWMachine.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/_ext/552806006/TS.o \
	${OBJECTDIR}/_ext/552806006/SWMachineB.o \
	${OBJECTDIR}/_ext/552806006/PTest.o \
	${OBJECTDIR}/_ext/552806006/TSB.o


# C Compiler Flags
CFLAGS=-S

# CC Compiler Flags
CCFLAGS=-S
CXXFLAGS=-S

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tplstate.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tplstate.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -O4 -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tplstate ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/552806006/SWMachine.o: /C/prog/c++/tplstate/SWMachine.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/552806006
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/552806006/SWMachine.o /C/prog/c++/tplstate/SWMachine.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/_ext/552806006/TS.o: /C/prog/c++/tplstate/TS.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/552806006
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/552806006/TS.o /C/prog/c++/tplstate/TS.cpp

${OBJECTDIR}/_ext/552806006/SWMachineB.o: /C/prog/c++/tplstate/SWMachineB.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/552806006
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/552806006/SWMachineB.o /C/prog/c++/tplstate/SWMachineB.cpp

${OBJECTDIR}/_ext/552806006/PTest.o: /C/prog/c++/tplstate/PTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/552806006
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/552806006/PTest.o /C/prog/c++/tplstate/PTest.cpp

${OBJECTDIR}/_ext/552806006/TSB.o: /C/prog/c++/tplstate/TSB.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/552806006
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/552806006/TSB.o /C/prog/c++/tplstate/TSB.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tplstate.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
