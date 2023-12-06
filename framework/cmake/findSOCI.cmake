# FindSOCI.cmake

set(SOCI_VERSION 4_1)

# Provide a hint for where to find SOCI
find_path(SOCI_INCLUDE_DIR
        NAMES soci/soci.h
        PATHS
        ${CMAKE_HOME_DIRECTORY}/soci/include
)

# Find the soci_core library
find_library(SOCI_CORE_LIBRARY
        NAMES soci_core_${SOCI_VERSION}
        PATHS
        ${CMAKE_HOME_DIRECTORY}/soci/lib/
)

# Find the soci_mysql library
find_library(SOCI_MYSQL_LIBRARY
        NAMES soci_mysql_${SOCI_VERSION}
        PATHS
        ${CMAKE_HOME_DIRECTORY}/soci/lib/
)

# Find the soci_odbc library
find_library(SOCI_ODBC_LIBRARY
        NAMES soci_odbc_${SOCI_VERSION}
        PATHS
        ${CMAKE_HOME_DIRECTORY}/soci/lib/
)

# Find the soci_empty library
find_library(SOCI_EMPTY_LIBRARY
        NAMES soci_empty_${SOCI_VERSION}
        PATHS
        ${CMAKE_HOME_DIRECTORY}/soci/lib/
)


# Check if everything was found
message(STATUS "${SOCI_INCLUDE_DIR}")
message(STATUS "${SOCI_CORE_LIBRARY}")
message(STATUS "${SOCI_MYSQL_LIBRARY}")
message(STATUS "${SOCI_ODBC_LIBRARY}")
message(STATUS "${SOCI_EMPTY_LIBRARY}")

if(SOCI_INCLUDE_DIR AND SOCI_CORE_LIBRARY AND SOCI_MYSQL_LIBRARY AND SOCI_ODBC_LIBRARY AND SOCI_EMPTY_LIBRARY)
    set(SOCI_FOUND TRUE)
    message(STATUS "Found SOCI")
else()
    set(SOCI_FOUND FALSE)
    message(STATUS "Not found SOCI")
endif()

# Provide variables for the user
if(SOCI_FOUND)

    set(SOCI_INCLUDE_DIRS ${SOCI_INCLUDE_DIR})
    set(SOCI_LIBRARIES ${SOCI_CORE_LIBRARY} ${SOCI_MYSQL_LIBRARY} ${SOCI_ODBC_LIBRARY} ${SOCI_EMPTY_LIBRARY})
endif()

# Provide imported target
add_library(SOCI::SOCI UNKNOWN IMPORTED)
set_target_properties(SOCI::SOCI PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${SOCI_INCLUDE_DIRS}"
        IMPORTED_LOCATION "${SOCI_CORE_LIBRARY}"
)

