#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "openGPMP" for configuration "Release"
set_property(TARGET openGPMP APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(openGPMP PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX;Fortran"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libopenGPMP.a"
  )

list(APPEND _cmake_import_check_targets openGPMP )
list(APPEND _cmake_import_check_files_for_openGPMP "${_IMPORT_PREFIX}/lib/libopenGPMP.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
