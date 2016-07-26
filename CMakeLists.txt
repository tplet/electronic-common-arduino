cmake_minimum_required(VERSION 3.3)

# Library name
set(NAME common-arduino)

# Files
file(GLOB_RECURSE FILES_CPP "com/*.cpp")
file(GLOB_RECURSE FILES_H "com/*.h")

# Ignores some paths
include(CMakeLists-ignore.txt)

# Define library
project("lib${NAME}")
add_library(${NAME} ${FILES_CPP} ${FILES_H})

# Permit to include files (similar as defining ./ directory to include path)
target_include_directories(${NAME} PUBLIC .)

## Dependencies
# EEPROM
add_subdirectory(./vendors/eeprom/)
target_link_libraries(${NAME} eeprom)
# LiquidCrystal
add_subdirectory(./vendors/LiquidCrystal/)
target_link_libraries(${NAME} LiquidCrystal)
