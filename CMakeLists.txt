cmake_minimum_required(VERSION 3.3)

# Library name
set(NAME common-arduino)

# Files
file(GLOB_RECURSE FILES_CPP "src/*.cpp")
file(GLOB_RECURSE FILES_H "src/*.h")

# Ignores some paths
include(CMakeLists-ignore.txt)

# Define library
project("lib${NAME}")
add_library(${NAME} ${FILES_CPP} ${FILES_H})

# Permit to include files (similar as defining ./ directory to include path)
target_include_directories(${NAME} PUBLIC .)

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
