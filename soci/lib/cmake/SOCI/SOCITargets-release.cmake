#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SOCI::soci_core_static" for configuration "Release"
set_property(TARGET SOCI::soci_core_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SOCI::soci_core_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsoci_core_4_1.lib"
  )

list(APPEND _cmake_import_check_targets SOCI::soci_core_static )
list(APPEND _cmake_import_check_files_for_SOCI::soci_core_static "${_IMPORT_PREFIX}/lib/libsoci_core_4_1.lib" )

# Import target "SOCI::soci_mysql_static" for configuration "Release"
set_property(TARGET SOCI::soci_mysql_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SOCI::soci_mysql_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsoci_mysql_4_1.lib"
  )

list(APPEND _cmake_import_check_targets SOCI::soci_mysql_static )
list(APPEND _cmake_import_check_files_for_SOCI::soci_mysql_static "${_IMPORT_PREFIX}/lib/libsoci_mysql_4_1.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
