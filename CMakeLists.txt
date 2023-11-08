#/************************************************************************* 
# *                                  
# *  Project               
# *                        __  __ _______ _____  _  __
# *                       |  \/  |__   __|  __ \| |/ /
# *  ___  _ __   ___ _ __ | \  / |  | |  | |__) | ' / 
# * / _ \| '_ \ / _ \ '_ \| |\/| |  | |  |  ___/|  <  
# *| (_) | |_) |  __/ | | | |  | |  | |  | |    | . \ 
# * \___/| .__/ \___|_| |_|_|  |_|  |_|  |_|    |_|\_\  
# *      | |                                          
# *      |_|                                         
# *
# *
# * Copyright (C) Akiel Aries, <akiel@akiel.org>.
# *
# * This software is licensed as described in the file LICENSE, which
# * you should have received as part of this distribution. The terms
# * among other details are referenced in the official documentation
# * seen here : https://akielaries.github.io/openGPMP/ along with 
# * important files seen in this project.
# *
# * You may opt to use, copy, modify, merge, publish, distribute 
# * and/or sell copies of the Software, and permit persons to whom 
# * the Software is furnished to do so, under the terms of the 
# * LICENSE file. As this is an Open Source effort, all implementations
# * must be of the same methodology.
# * 
# *
# * This software is distributed on an "AS IS" basis, WITHOUT 
# * WARRANTY OF ANY KIND, either express or implied.
# *
# ************************************************************************/

cmake_minimum_required(VERSION 3.18)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "-march=native -g -Wno-unused-result -Wparentheses \
                      -Wsign-compare -DNDEBUG -Wall -Wextra"
)

project(openGPMP VERSION 1.0 LANGUAGES CXX C ASM Fortran)

set(DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include(GNUInstallDirs)

option(BUILD_ARITH "[!] Build Arithmetic Module" ON)

############################################################
# Run Tests
############################################################
#find_package(GTest REQUIRED)

enable_testing()

add_subdirectory(tests)

############################################################
# Create a library
############################################################

# Add the module directories

add_subdirectory(modules/arithmetic)
add_subdirectory(modules/calculus)
add_subdirectory(modules/linalg)
add_subdirectory(modules/core)
add_subdirectory(modules/ml)
add_subdirectory(modules/nt)

add_library(${PROJECT_NAME} STATIC
  $<TARGET_OBJECTS:arithmetic>
  $<TARGET_OBJECTS:calculus>
  $<TARGET_OBJECTS:linalg>
  $<TARGET_OBJECTS:core>
  $<TARGET_OBJECTS:ml>
  $<TARGET_OBJECTS:nt>
)

# include directory for openGPMP
target_include_directories(${PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE modules
)

set_target_properties(${PROJECT_NAME} 
    PROPERTIES
    VERSION ${PROJECT_VERSION}
)

install(TARGETS ${PROJECT_NAME} EXPORT openGPMPConfig 
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# install include directory to /usr/local/include/openGPMP
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/openGPMP"
)

install(EXPORT openGPMPConfig DESTINATION share/openGPMP/cmake)

export(TARGETS ${PROJECT_NAME} FILE openGPMPConfig.cmake)

# run C++ and Fortran unit tests
add_dependencies(${PROJECT_NAME} RUN_CPP_TESTS)
add_dependencies(${PROJECT_NAME} RUN_FORTRAN_TESTS) 

# uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

