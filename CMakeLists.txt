cmake_minimum_required(VERSION 3.18.1)
project(hke VERSION 0.1.0)

# Options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

file(GLOB SRC_FILES CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")
message(src: ${SRC_FILES})

# Find libraries
include(FindPkgConfig)
pkg_check_modules(LIBEV REQUIRED libevdev)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBEV_INCLUDES})
target_link_libraries(${PROJECT_NAME} ${LIBEV_LIBRARIES})