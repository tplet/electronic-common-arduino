cmake_minimum_required(VERSION 3.3)

# Library name
set(NAME common-arduino)

# Files
file(GLOB_RECURSE FILES_CPP "src/*.cpp")
file(GLOB_RECURSE FILES_H "src/*.h")

# Ignores some paths
include(CMakeLists-ignore.txt)

# ARDUINO MODE
if (ARDUINO_FOUND)
    ## Dependencies
    # RTC (library)
    include_directories(./vendors/RTClib)
    add_subdirectory(./vendors/RTClib)
    # Common (library)
    include_directories(./vendors/common)
    add_subdirectory(./vendors/common/)

    # Declare arduino library
    generate_arduino_library(
        ${NAME}
        SRCS ${FILES_CPP}
        HDRS ${FILES_H}
        BOARD ${BOARD}
        ARDLIBS Wire SPI EEPROM LiquidCrystal
        LIBS common RTClib
#        NO_AUTOLIBS
    )

    # StandardCplusplus (add root path of this library to include path)
    target_include_directories(${NAME} PUBLIC ./vendors/common/vendors/StandardCplusplus)

# OTHER MODE (Raspberry)
else()
    # Define library
    project("lib${NAME}")
    add_library(${NAME} ${FILES_CPP} ${FILES_H})

    ## Dependencies
    # Common
    add_subdirectory(./vendors/common/)
    target_link_libraries(${NAME} common)
    # EEPROM
    add_subdirectory(./vendors/eeprom/)
    target_link_libraries(${NAME} eeprom)
    # LiquidCrystal
    add_subdirectory(./vendors/LiquidCrystal/)
    target_link_libraries(${NAME} LiquidCrystal)
    # RTC
    add_subdirectory(./vendors/RTClib)
    target_link_libraries(${NAME} RTC)

endif()

# Compiler
set_property(TARGET ${NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

# Permit to include files (similar as defining ./ directory to include path)
target_include_directories(${NAME} PUBLIC .)

# Add src directory to "include path"
target_include_directories(${NAME} PUBLIC ./src)

# Add vendors directory to "include path"
target_include_directories(${NAME} PUBLIC ./vendors)
