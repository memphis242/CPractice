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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/8055285/main.o \
	${OBJECTDIR}/_ext/7f3eff4c/main.o \
	${OBJECTDIR}/_ext/a5b8c547/EncoderInterface.o \
	${OBJECTDIR}/_ext/a5b8c547/GpsInterface.o \
	${OBJECTDIR}/_ext/a5b8c547/LidarInterface.o \
	${OBJECTDIR}/_ext/a5b8c547/RS232_GenericController.o \
	${OBJECTDIR}/_ext/a5b8c547/RoboteQ.o \
	${OBJECTDIR}/_ext/a5b8c547/TCP_Connection.o \
	${OBJECTDIR}/_ext/a5b8c547/XboxControllerInterface.o \
	${OBJECTDIR}/_ext/2db7bc07/Colors.o \
	${OBJECTDIR}/_ext/d3ef045a/encoderTest.o \
	${OBJECTDIR}/_ext/d3ef045a/rs232.o \
	${OBJECTDIR}/_ext/d3ef045a/sickSensor.o \
	${OBJECTDIR}/_ext/d3ef045a/xboxMotorBridge.o \
	${OBJECTDIR}/_ext/d3ef045a/xboxcontroller.o \
	${OBJECTDIR}/main.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/encoder

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/encoder: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/encoder ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/8055285/main.o: ../../../snowplow/drivers/old/GPS/main.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/8055285
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/8055285/main.o ../../../snowplow/drivers/old/GPS/main.cpp

${OBJECTDIR}/_ext/7f3eff4c/main.o: ../../../snowplow/drivers/old/MotorController/main.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/7f3eff4c
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7f3eff4c/main.o ../../../snowplow/drivers/old/MotorController/main.cpp

${OBJECTDIR}/_ext/a5b8c547/EncoderInterface.o: ../../../snowplow/drivers/src/EncoderInterface.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a5b8c547
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a5b8c547/EncoderInterface.o ../../../snowplow/drivers/src/EncoderInterface.cpp

${OBJECTDIR}/_ext/a5b8c547/GpsInterface.o: ../../../snowplow/drivers/src/GpsInterface.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a5b8c547
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a5b8c547/GpsInterface.o ../../../snowplow/drivers/src/GpsInterface.cpp

${OBJECTDIR}/_ext/a5b8c547/LidarInterface.o: ../../../snowplow/drivers/src/LidarInterface.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a5b8c547
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a5b8c547/LidarInterface.o ../../../snowplow/drivers/src/LidarInterface.cpp

${OBJECTDIR}/_ext/a5b8c547/RS232_GenericController.o: ../../../snowplow/drivers/src/RS232_GenericController.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a5b8c547
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a5b8c547/RS232_GenericController.o ../../../snowplow/drivers/src/RS232_GenericController.cpp

${OBJECTDIR}/_ext/a5b8c547/RoboteQ.o: ../../../snowplow/drivers/src/RoboteQ.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a5b8c547
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a5b8c547/RoboteQ.o ../../../snowplow/drivers/src/RoboteQ.cpp

${OBJECTDIR}/_ext/a5b8c547/TCP_Connection.o: ../../../snowplow/drivers/src/TCP_Connection.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a5b8c547
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a5b8c547/TCP_Connection.o ../../../snowplow/drivers/src/TCP_Connection.cpp

${OBJECTDIR}/_ext/a5b8c547/XboxControllerInterface.o: ../../../snowplow/drivers/src/XboxControllerInterface.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a5b8c547
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a5b8c547/XboxControllerInterface.o ../../../snowplow/drivers/src/XboxControllerInterface.cpp

${OBJECTDIR}/_ext/2db7bc07/Colors.o: ../../../snowplow/drivers/src/misc-libs/Colors.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2db7bc07
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2db7bc07/Colors.o ../../../snowplow/drivers/src/misc-libs/Colors.cpp

${OBJECTDIR}/_ext/d3ef045a/encoderTest.o: ../../../snowplow/drivers/src/test/encoderTest.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d3ef045a
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d3ef045a/encoderTest.o ../../../snowplow/drivers/src/test/encoderTest.cpp

${OBJECTDIR}/_ext/d3ef045a/rs232.o: ../../../snowplow/drivers/src/test/rs232.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d3ef045a
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d3ef045a/rs232.o ../../../snowplow/drivers/src/test/rs232.cpp

${OBJECTDIR}/_ext/d3ef045a/sickSensor.o: ../../../snowplow/drivers/src/test/sickSensor.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d3ef045a
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d3ef045a/sickSensor.o ../../../snowplow/drivers/src/test/sickSensor.cpp

${OBJECTDIR}/_ext/d3ef045a/xboxMotorBridge.o: ../../../snowplow/drivers/src/test/xboxMotorBridge.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d3ef045a
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d3ef045a/xboxMotorBridge.o ../../../snowplow/drivers/src/test/xboxMotorBridge.cpp

${OBJECTDIR}/_ext/d3ef045a/xboxcontroller.o: ../../../snowplow/drivers/src/test/xboxcontroller.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d3ef045a
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d3ef045a/xboxcontroller.o ../../../snowplow/drivers/src/test/xboxcontroller.cpp

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

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
