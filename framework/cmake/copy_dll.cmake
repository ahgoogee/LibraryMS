
function(copy_dll DLL_FILENAME)
    if("${CMAKE_GENERATOR}" MATCHES "Visual Studio")
        # if (CMAKE_BUILD_TYPE STREQUAL "Release")
            file(COPY ${DLL_FILENAME} DESTINATION Release)
            message(STATUS "Copy ${DLL_FILENAME} to ${CMAKE_CURRENT_BINARY_DIR}/Release")
        # elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
            file(COPY ${DLL_FILENAME} DESTINATION Debug)
            message(STATUS "Copy ${DLL_FILENAME} to ${CMAKE_CURRENT_BINARY_DIR}/Debug")
        # endif ()
    else ()
        file(COPY ${DLL_FILENAME} DESTINATION .)
        message(STATUS "Copy ${DLL_FILENAME} to ${CMAKE_CURRENT_BINARY_DIR}")
    endif ()
endfunction()


