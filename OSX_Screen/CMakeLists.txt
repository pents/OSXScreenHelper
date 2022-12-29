add_library(OSX_Screen "")

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
