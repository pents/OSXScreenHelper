add_library(OSX_Screen "")

find_package(OpenCV REQUIRED)

include_directories (
        ${OpenCV_INCLUDE_DIRS}
)

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
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/ScreenHelper.h
        ${CMAKE_CURRENT_LIST_DIR}/ScreenHelperExternal.h
        ${CMAKE_CURRENT_LIST_DIR}/OpenCV.h
        )

target_include_directories(OSX_Screen
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )
