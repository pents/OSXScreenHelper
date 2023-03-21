add_library(Utils)

target_sources(Utils
        PUBLIC
        Stopwatch/Implementation/Stopwatch.cpp
        )

target_include_directories(Utils
        PUBLIC
        Stopwatch/Headers
        )

