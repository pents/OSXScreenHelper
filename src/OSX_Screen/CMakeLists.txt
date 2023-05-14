add_library(OSX_Screen SHARED "")
message(-------------------CMAKE_OSX_ARCHITECTURES: ${CMAKE_OSX_ARCHITECTURES})

IF (CMAKE_OSX_ARCHITECTURES STREQUAL "x86_64")
    SET(CMAKE_PREFIX_PATH "/usr/local")
    SET(OpenCV_DIR "/usr/local/lib/cmake/opencv4")
ELSE()
    SET(CMAKE_PREFIX_PATH "/opt/homebrew")
    SET(OpenCV_DIR "/opt/homebrew/opt/opencv")
ENDIF()


find_package(OpenCV REQUIRED CONFIG)


include_directories (
        ${OpenCV_INCLUDE_DIRS}
)

message(---------------------------------------CMAKE_CURRENT_LIST_DIR: .)
message(---------------------------------------OpenCV_LIBS: ${OpenCV_LIBS})
message(---------------------------------------OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS})

target_link_libraries(
        OSX_Screen
        PUBLIC
        "-framework CoreGraphics"
        "-framework Foundation"
        "-framework CoreServices"
        "-framework ImageIO"
        "-framework ApplicationServices"
        ${OpenCV_LIBS}
        )


target_sources(OSX_Screen
        PUBLIC
        Implementation/OpenCV.cpp
        Implementation/ScreenHelper.cpp
        Implementation/ScreenHelperExternal.cpp
        Implementation/ScreenHelperCachedExternal.cpp
        )

target_include_directories(OSX_Screen
        PUBLIC
        Headers
        "/Library/CImg"
        )

add_subdirectory(Common)
add_subdirectory(Exceptions)

