cmake_minimum_required(VERSION 3.3)

project(market_data)

cmake_policy(SET CMP0077 OLD)

set(LIBRARY_BUILD_TYPES "")

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

# Set default to static if user didn't specify what library type to build
if (NOT ${BUILD_STATIC} AND NOT ${BUILD_SHARED} AND NOT ${BUILD_HEADER} AND NOT ${BUILD_SRC})
    set(BUILD_STATIC ON)
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/market_data")

if (${BUILD_TESTS})
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/test")
endif()