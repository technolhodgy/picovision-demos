cmake_minimum_required(VERSION 3.12)

set(NAME pico-vision)
# Add your source files
add_executable(${NAME}
    main.cpp # <-- Add source files here!
)

# Don't forget to link the libraries you need!
#target_link_libraries(${NAME}
#    hardware_uart
#    picovision
#    pico_graphics
#)
# TODO: Don't forget to link the libraries you need!
target_link_libraries(${NAME}
pico_stdlib
    hardware_uart
    picovision
    pico_graphics
    jpegdec
    pimoroni_i2c
    fatfs
    sdcard
)

pico_enable_stdio_usb(${NAME} 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(${NAME})

# Set up files for the release packages
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.uf2
    ${CMAKE_CURRENT_LIST_DIR}/README.md
    DESTINATION .
)

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP" "TGZ")
include(CPack)
