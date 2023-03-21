IF (APPLE)
    message ("Apple detected")
    add_subdirectory(OSX_Screen)
    add_subdirectory(Utils)

ELSE()

# TODO: Place win library here
        
ENDIF()

