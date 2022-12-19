cmake_minimum_required(VERSION 3.24)

project(openMTPK VERSION 0.1 LANGUAGES CXX)

set(DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include(GNUInstallDirs)

############################################################
# Create a library
############################################################
set(SOURCE_FILES 
    modules/arithmetic/arith.cpp
    modules/calculus/deriv.cpp
    modules/linalg/lao.cpp
    modules/ml/linreg.cpp
    modules/number_theory/cipher.cpp
    modules/number_theory/rc4.cpp
    modules/number_theory/primes.cpp
)

add_library(${PROJECT_NAME} ...)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE modules
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

install(TARGETS ${PROJECT_NAME} EXPORT openMTPKConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(EXPORT opentMTPKConfig DESTINATION share/openMTPK/cmake)

export(TARGETS ${PROJECT_NAME} FILES opentMTPKConfig.cmake)

