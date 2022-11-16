add_library(OSX_Screen "")

target_sources(OSX_Screen
        PRIVATE
        ScreenHelper.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/ScreenHelper.h
        )

target_include_directories(OSX_Screen
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )