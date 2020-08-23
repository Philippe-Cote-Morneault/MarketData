cmake_minimum_required(VERSION 3.12)
project(YahooFinance)

set(CMAKE_CXX_STANDARD 11)

find_package(CURL REQUIRED)

set(BUILD_TESTS OFF)
option(BUILD_TESTS "BUILD_TESTS" OFF)

add_library(YahooFinance INTERFACE)
target_include_directories(YahooFinance INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}> $<INSTALL_INTERFACE:include>)
install(TARGETS YahooFinance EXPORT YahooFinanceExport)
install(EXPORT YahooFinanceExport NAMESPACE Upstream::
        DESTINATION lib/cmake/PythonFinance
        )

if (BUILD_TESTS)
    add_executable(test test/Test.cpp)
    target_link_libraries(test ${CURL_LIBRARIES})
    target_link_libraries(test YahooFinance)
endif()
