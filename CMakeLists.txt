cmake_minimum_required(VERSION 3.12)

include(pimoroni_pico_import.cmake)
include(pico_sdk_import.cmake)

# Gooey demos
project(picovision-demos C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

include(picovision_import.cmake)

# Include required libraries
# This assumes `pimoroni-pico` is stored alongside your project

# I2C and SPI
include(common/pimoroni_i2c)
include(common/pimoroni_bus)

include(libraries/jpegdec/jpegdec)
include(libraries/pico_graphics/pico_graphics)

# SD Card Access
include(drivers/fatfs/fatfs)
include(drivers/sdcard/sdcard)

add_subdirectory(screenmodes)
add_subdirectory(buttons)
add_subdirectory(drawing)
add_subdirectory(picovision)
