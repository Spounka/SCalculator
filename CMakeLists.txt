cmake_minimum_required(VERSION 3.10)
project(SCalculator)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_INSTALL_PREFIX "/usr")


find_package(PkgConfig REQUIRED)
pkg_search_module(GTKMM gtkmm-3.0 REQUIRED)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

include_directories(src)

add_subdirectory(src)
add_subdirectory(app)

install(TARGETS SCalculator DESTINATION "bin/")
install(DIRECTORY "scalculator" DESTINATION "share/")
install(TARGETS SCalculatorLib DESTINATION "lib/")
