project(ScreenHelper)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 20)


add_executable(screenHelperTest main.cpp)

add_subdirectory(OSX_Screen)

target_link_libraries(screenHelperTest
        PUBLIC
        "-framework CoreGraphics"
        "-framework Foundation"
        "-framework CoreServices"
        "-framework ImageIO"
        PRIVATE
        OSX_Screen
        )

#set(CMAKE_OSX_ARCHITECTURES "x86_64")
