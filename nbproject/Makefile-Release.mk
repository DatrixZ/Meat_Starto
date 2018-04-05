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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Animator.o \
	${OBJECTDIR}/AssetManager.o \
	${OBJECTDIR}/Player.o \
	${OBJECTDIR}/Tile.o \
	${OBJECTDIR}/boss.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/mj_t.o \
	${OBJECTDIR}/physicsEngine/contactListener.o \
	${OBJECTDIR}/physicsEngine/pBody.o \
	${OBJECTDIR}/physicsEngine/pConverter.o \
	${OBJECTDIR}/physicsEngine/physicsEngine.o \
	${OBJECTDIR}/renderEngine.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meat_starto

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meat_starto: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meat_starto ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Animator.o: Animator.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Animator.o Animator.cpp

${OBJECTDIR}/AssetManager.o: AssetManager.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AssetManager.o AssetManager.cpp

${OBJECTDIR}/Player.o: Player.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Player.o Player.cpp

${OBJECTDIR}/Tile.o: Tile.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Tile.o Tile.cpp

${OBJECTDIR}/boss.o: boss.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/boss.o boss.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/mj_t.o: mj_t.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mj_t.o mj_t.cpp

${OBJECTDIR}/physicsEngine/contactListener.o: physicsEngine/contactListener.cpp
	${MKDIR} -p ${OBJECTDIR}/physicsEngine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/physicsEngine/contactListener.o physicsEngine/contactListener.cpp

${OBJECTDIR}/physicsEngine/pBody.o: physicsEngine/pBody.cpp
	${MKDIR} -p ${OBJECTDIR}/physicsEngine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/physicsEngine/pBody.o physicsEngine/pBody.cpp

${OBJECTDIR}/physicsEngine/pConverter.o: physicsEngine/pConverter.cpp
	${MKDIR} -p ${OBJECTDIR}/physicsEngine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/physicsEngine/pConverter.o physicsEngine/pConverter.cpp

${OBJECTDIR}/physicsEngine/physicsEngine.o: physicsEngine/physicsEngine.cpp
	${MKDIR} -p ${OBJECTDIR}/physicsEngine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/physicsEngine/physicsEngine.o physicsEngine/physicsEngine.cpp

${OBJECTDIR}/renderEngine.o: renderEngine.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/renderEngine.o renderEngine.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
