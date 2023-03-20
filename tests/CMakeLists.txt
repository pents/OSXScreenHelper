add_executable(screenHelperTest ScreenHelperTests.cpp)

target_link_libraries(screenHelperTest
        PRIVATE
        OSX_Screen
        )

target_sources(screenHelperTest
        PUBLIC
        .
        )

target_include_directories(screenHelperTest
        PUBLIC
        .
        )