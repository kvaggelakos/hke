cmake_minimum_required(VERSION 3.18.1)
project(hke VERSION 0.1.0)

# Options
set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC_FILES CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")
message(src: ${SRC_FILES})

# Find libraries
include(FindPkgConfig)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)
# find_path(LIBUSB_INCLUDE_DIR
#   NAMES libusb.h
#   PATH_SUFFIXES "include" "libusb" "libusb-1.0")
# find_library(LIBUSB_LIBRARY
#   NAMES usb
#   PATH_SUFFIXES "lib" "lib32" "lib64")
# message(usbinclude: ${LIBUSB_INCLUDE_DIR}, usblibrary: ${LIBUSB_LIBRARY})

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBUSB_INCLUDES})
target_link_libraries(${PROJECT_NAME} ${LIBUSB_LIBRARIES})