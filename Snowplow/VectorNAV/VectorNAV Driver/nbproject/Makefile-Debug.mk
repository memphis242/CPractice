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
	${OBJECTDIR}/_ext/8f25304f/vectorNAVinterface.o \
	${OBJECTDIR}/_ext/921ab625/demo_rx.o \
	${OBJECTDIR}/_ext/921ab625/demo_tx.o \
	${OBJECTDIR}/_ext/921ab625/rs232.o \
	${OBJECTDIR}/vnlibrary/examples/ez_async_data/main.o \
	${OBJECTDIR}/vnlibrary/examples/getting_started/uartpractice.o \
	${OBJECTDIR}/vnlibrary/examples/sensor/generalpractice.o \
	${OBJECTDIR}/vnlibrary/examples/spi/main.o \
	${OBJECTDIR}/vnlibrary/include/vectorNAVinterface.o \
	${OBJECTDIR}/vnlibrary/src/vn/conv.o \
	${OBJECTDIR}/vnlibrary/src/vn/error.o \
	${OBJECTDIR}/vnlibrary/src/vn/error_detection.o \
	${OBJECTDIR}/vnlibrary/src/vn/math/matrix.o \
	${OBJECTDIR}/vnlibrary/src/vn/math/vector.o \
	${OBJECTDIR}/vnlibrary/src/vn/protocol/spi.o \
	${OBJECTDIR}/vnlibrary/src/vn/protocol/upack.o \
	${OBJECTDIR}/vnlibrary/src/vn/protocol/upackf.o \
	${OBJECTDIR}/vnlibrary/src/vn/sensors.o \
	${OBJECTDIR}/vnlibrary/src/vn/sensors/compositedata.o \
	${OBJECTDIR}/vnlibrary/src/vn/sensors/ezasyncdata.o \
	${OBJECTDIR}/vnlibrary/src/vn/sensors/searcher.o \
	${OBJECTDIR}/vnlibrary/src/vn/util.o \
	${OBJECTDIR}/vnlibrary/src/vn/xplat/criticalsection.o \
	${OBJECTDIR}/vnlibrary/src/vn/xplat/event.o \
	${OBJECTDIR}/vnlibrary/src/vn/xplat/serialport.o \
	${OBJECTDIR}/vnlibrary/src/vn/xplat/thread.o \
	${OBJECTDIR}/vnlibrary/src/vn/xplat/time.o \
	${OBJECTDIR}/vntest.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/vectornav_driver

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/vectornav_driver: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/vectornav_driver ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/8f25304f/vectorNAVinterface.o: ../../../../../Downloads/Snowplow/Sensors/IMU/VectorNAV/vnproglib-1.1/c/include/vectorNAVinterface.c
	${MKDIR} -p ${OBJECTDIR}/_ext/8f25304f
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/8f25304f/vectorNAVinterface.o ../../../../../Downloads/Snowplow/Sensors/IMU/VectorNAV/vnproglib-1.1/c/include/vectorNAVinterface.c

${OBJECTDIR}/_ext/921ab625/demo_rx.o: ../../RS-232/demo_rx.c
	${MKDIR} -p ${OBJECTDIR}/_ext/921ab625
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/921ab625/demo_rx.o ../../RS-232/demo_rx.c

${OBJECTDIR}/_ext/921ab625/demo_tx.o: ../../RS-232/demo_tx.c
	${MKDIR} -p ${OBJECTDIR}/_ext/921ab625
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/921ab625/demo_tx.o ../../RS-232/demo_tx.c

${OBJECTDIR}/_ext/921ab625/rs232.o: ../../RS-232/rs232.c
	${MKDIR} -p ${OBJECTDIR}/_ext/921ab625
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/921ab625/rs232.o ../../RS-232/rs232.c

${OBJECTDIR}/vnlibrary/examples/ez_async_data/main.o: vnlibrary/examples/ez_async_data/main.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/examples/ez_async_data
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/examples/ez_async_data/main.o vnlibrary/examples/ez_async_data/main.c

${OBJECTDIR}/vnlibrary/examples/getting_started/uartpractice.o: vnlibrary/examples/getting_started/uartpractice.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/examples/getting_started
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/examples/getting_started/uartpractice.o vnlibrary/examples/getting_started/uartpractice.c

${OBJECTDIR}/vnlibrary/examples/sensor/generalpractice.o: vnlibrary/examples/sensor/generalpractice.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/examples/sensor
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/examples/sensor/generalpractice.o vnlibrary/examples/sensor/generalpractice.c

${OBJECTDIR}/vnlibrary/examples/spi/main.o: vnlibrary/examples/spi/main.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/examples/spi
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/examples/spi/main.o vnlibrary/examples/spi/main.c

${OBJECTDIR}/vnlibrary/include/vectorNAVinterface.o: vnlibrary/include/vectorNAVinterface.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/include
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/include/vectorNAVinterface.o vnlibrary/include/vectorNAVinterface.c

${OBJECTDIR}/vnlibrary/src/vn/conv.o: vnlibrary/src/vn/conv.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/src/vn
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/src/vn/conv.o vnlibrary/src/vn/conv.c

${OBJECTDIR}/vnlibrary/src/vn/error.o: vnlibrary/src/vn/error.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/src/vn
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/src/vn/error.o vnlibrary/src/vn/error.c

${OBJECTDIR}/vnlibrary/src/vn/error_detection.o: vnlibrary/src/vn/error_detection.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/src/vn
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/src/vn/error_detection.o vnlibrary/src/vn/error_detection.c

${OBJECTDIR}/vnlibrary/src/vn/math/matrix.o: vnlibrary/src/vn/math/matrix.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/src/vn/math
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/src/vn/math/matrix.o vnlibrary/src/vn/math/matrix.c

${OBJECTDIR}/vnlibrary/src/vn/math/vector.o: vnlibrary/src/vn/math/vector.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/src/vn/math
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/src/vn/math/vector.o vnlibrary/src/vn/math/vector.c

${OBJECTDIR}/vnlibrary/src/vn/protocol/spi.o: vnlibrary/src/vn/protocol/spi.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/src/vn/protocol
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/src/vn/protocol/spi.o vnlibrary/src/vn/protocol/spi.c

${OBJECTDIR}/vnlibrary/src/vn/protocol/upack.o: vnlibrary/src/vn/protocol/upack.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/src/vn/protocol
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/src/vn/protocol/upack.o vnlibrary/src/vn/protocol/upack.c

${OBJECTDIR}/vnlibrary/src/vn/protocol/upackf.o: vnlibrary/src/vn/protocol/upackf.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/src/vn/protocol
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/src/vn/protocol/upackf.o vnlibrary/src/vn/protocol/upackf.c

${OBJECTDIR}/vnlibrary/src/vn/sensors.o: vnlibrary/src/vn/sensors.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/src/vn
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/src/vn/sensors.o vnlibrary/src/vn/sensors.c

${OBJECTDIR}/vnlibrary/src/vn/sensors/compositedata.o: vnlibrary/src/vn/sensors/compositedata.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/src/vn/sensors
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/src/vn/sensors/compositedata.o vnlibrary/src/vn/sensors/compositedata.c

${OBJECTDIR}/vnlibrary/src/vn/sensors/ezasyncdata.o: vnlibrary/src/vn/sensors/ezasyncdata.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/src/vn/sensors
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/src/vn/sensors/ezasyncdata.o vnlibrary/src/vn/sensors/ezasyncdata.c

${OBJECTDIR}/vnlibrary/src/vn/sensors/searcher.o: vnlibrary/src/vn/sensors/searcher.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/src/vn/sensors
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/src/vn/sensors/searcher.o vnlibrary/src/vn/sensors/searcher.c

${OBJECTDIR}/vnlibrary/src/vn/util.o: vnlibrary/src/vn/util.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/src/vn
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/src/vn/util.o vnlibrary/src/vn/util.c

${OBJECTDIR}/vnlibrary/src/vn/xplat/criticalsection.o: vnlibrary/src/vn/xplat/criticalsection.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/src/vn/xplat
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/src/vn/xplat/criticalsection.o vnlibrary/src/vn/xplat/criticalsection.c

${OBJECTDIR}/vnlibrary/src/vn/xplat/event.o: vnlibrary/src/vn/xplat/event.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/src/vn/xplat
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/src/vn/xplat/event.o vnlibrary/src/vn/xplat/event.c

${OBJECTDIR}/vnlibrary/src/vn/xplat/serialport.o: vnlibrary/src/vn/xplat/serialport.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/src/vn/xplat
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/src/vn/xplat/serialport.o vnlibrary/src/vn/xplat/serialport.c

${OBJECTDIR}/vnlibrary/src/vn/xplat/thread.o: vnlibrary/src/vn/xplat/thread.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/src/vn/xplat
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/src/vn/xplat/thread.o vnlibrary/src/vn/xplat/thread.c

${OBJECTDIR}/vnlibrary/src/vn/xplat/time.o: vnlibrary/src/vn/xplat/time.c
	${MKDIR} -p ${OBJECTDIR}/vnlibrary/src/vn/xplat
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vnlibrary/src/vn/xplat/time.o vnlibrary/src/vn/xplat/time.c

${OBJECTDIR}/vntest.o: vntest.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vntest.o vntest.c

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
