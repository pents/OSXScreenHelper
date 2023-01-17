set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE INTERNAL "" FORCE)
cmake_policy(SET CMP0048 NEW)
set(CMAKE_BUILD_TYPE Release)ћ

project(ScreenHelper VERSION 1.0.0 DESCRIPTION "OSX Library for screen actions")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_OSX_ARCHITECTURES})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_OSX_ARCHITECTURES})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_OSX_ARCHITECTURES})

cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)

add_executable(screenHelperTest main.cpp)

IF (APPLE)
    message ("Apple detected")
    add_subdirectory(OSX_Screen)


    target_link_libraries(screenHelperTest
            PRIVATE
            OSX_Screen
            )

ELSE()

# TODO: Place win library here
        
ENDIF()

