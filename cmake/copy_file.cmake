
function(copy_file FILENAME)
    if("${CMAKE_GENERATOR}" MATCHES "Visual Studio")
        # if (CMAKE_BUILD_TYPE STREQUAL "Release")
            file(COPY ${FILENAME} DESTINATION Release)
            message(STATUS "Copy ${FILENAME} to ${CMAKE_CURRENT_BINARY_DIR}/Release")
        # elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
            file(COPY ${FILENAME} DESTINATION Debug)
            message(STATUS "Copy ${FILENAME} to ${CMAKE_CURRENT_BINARY_DIR}/Debug")
        # endif ()
    else ()
        file(COPY ${FILENAME} DESTINATION .)
        message(STATUS "Copy ${FILENAME} to ${CMAKE_CURRENT_BINARY_DIR}")
    endif ()
endfunction()


