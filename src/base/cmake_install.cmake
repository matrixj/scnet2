# Install script for directory: /home/jmchen/work/scnet2/src/base

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/jmchen/work/build/debug-install")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/jmchen/work/scnet2/lib/libscnet2_base.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/scnet2/base" TYPE FILE FILES
    "/home/jmchen/work/scnet2/src/base/copyable.h"
    "/home/jmchen/work/scnet2/src/base/types.h"
    "/home/jmchen/work/scnet2/src/base/logbuffer.h"
    "/home/jmchen/work/scnet2/src/base/timer.h"
    "/home/jmchen/work/scnet2/src/base/channel.h"
    "/home/jmchen/work/scnet2/src/base/baseloop.h"
    "/home/jmchen/work/scnet2/src/base/printer.h"
    "/home/jmchen/work/scnet2/src/base/current_thread.h"
    "/home/jmchen/work/scnet2/src/base/thread.h"
    "/home/jmchen/work/scnet2/src/base/countdown_latch.h"
    "/home/jmchen/work/scnet2/src/base/mutexlock.h"
    "/home/jmchen/work/scnet2/src/base/typedef_callback.h"
    "/home/jmchen/work/scnet2/src/base/buffer.h"
    "/home/jmchen/work/scnet2/src/base/time.h"
    "/home/jmchen/work/scnet2/src/base/sclog.h"
    "/home/jmchen/work/scnet2/src/base/condition.h"
    "/home/jmchen/work/scnet2/src/base/atomic_int.h"
    "/home/jmchen/work/scnet2/src/base/logger.h"
    "/home/jmchen/work/scnet2/src/base/timestamp.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/jmchen/work/scnet2/src/base/tests/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

