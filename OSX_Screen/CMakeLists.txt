add_library(OSX_Screen SHARED "")

IF (CMAKE_OSX_ARCHITECTURES STREQUAL "x86_64")
    message(-------------------CMAKE_OSX_ARCHITECTURES: ${CMAKE_OSX_ARCHITECTURES})
    SET(OpenCV_DIR "/usr/local/Cellar/opencv/4.7.0/include/opencv4")
ELSE()
    SET(OpenCV_DIR "/opt/homebrew/Cellar/opencv/4.7.0/include/opencv4")
ENDIF()

message(-------------------OpenCV_DIR: ${OpenCV_DIR})
find_package(OpenCV REQUIRED)
message(-------------------OpenCV_DIR: ${OpenCV_DIR})

include_directories (
        ${OpenCV_INCLUDE_DIRS}
)

message(CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR})
message(OpenCV_LIBS: ${OpenCV_LIBS})
message(OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS})

target_link_libraries(
        OSX_Screen
        PUBLIC
        "-framework CoreGraphics"
        "-framework Foundation"
        "-framework CoreServices"
        "-framework ImageIO"
        "-framework ApplicationServices"
        PRIVATE
        ${OpenCV_LIBS}
        )


target_sources(OSX_Screen
        PRIVATE
        ScreenHelper.cpp
        OpenCV.cpp
        ScreenHelperExternal.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/ScreenHelper.h
        ${CMAKE_CURRENT_LIST_DIR}/ScreenHelperExternal.h
        ${CMAKE_CURRENT_LIST_DIR}/OpenCV.h
        )

target_include_directories(OSX_Screen
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

