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
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

#target_sources(${PROJECT_NAME} PUBLIC FILE_SET HEADERS
#    BASE_DIRS ${OPENMTPK_SOURCE_DIR}
#    FILES ${OPENMTPK_SOURCE_DIR}/include
#)

target_include_directories(${PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE modules
)

# headers to declare as public
set(OPM_INCLUDES
    ${PROJECT_SOURCE_DIR}/include/arithmetic/arith.hpp
    ${PROJECT_SOURCE_DIR}/include/calculus/deriv.hpp
    ${PROJECT_SOURCE_DIR}/include/linalg/lao.hpp
    ${PROJECT_SOURCE_DIR}/include/ml/linreg.hpp
    ${PROJECT_SOURCE_DIR}/include/number_theory/cipher.hpp
    ${PROJECT_SOURCE_DIR}/include/number_theory/rc4.hpp
    ${PROJECT_SOURCE_DIR}/include/number_theory/primes.hpp
)

set_target_properties(${PROJECT_NAME} 
    PROPERTIES
    PUBLIC_HEADER "${OPM_INCLUDES}"
    VERSION ${PROJECT_VERSION}
)

install(TARGETS ${PROJECT_NAME} EXPORT openMTPKConfig 
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER 
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/openMTPK"
)

install(EXPORT openMTPKConfig DESTINATION share/openMTPK/cmake)

export(TARGETS ${PROJECT_NAME} FILE openMTPKConfig.cmake)

