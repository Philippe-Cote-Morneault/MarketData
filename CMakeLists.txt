cmake_minimum_required(VERSION 3.3)

project(market_data)

cmake_policy(SET CMP0077 OLD)

set(BUILD_TESTS OFF)
option(BUILD_TESTS "Build tests" OFF)
set(BUILD_STATIC OFF)
option(BUILD_STATIC "Build static library" OFF)
set(BUILD_SHARED OFF)
option(BUILD_SHARED "Build shared library" OFF)
set(BUILD_HEADER OFF)
option(BUILD_HEADER "Build header-only libray" OFF)
set(BUILD_SRC OFF)
option(BUILD_SRC "Build source library" OFF)

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/market_data")

if (${BUILD_TESTS})
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/test")
endif()