cmake_minimum_required(VERSION 3.3)

project(market_data)

cmake_policy(SET CMP0076 OLD)

set(CMAKE_CXX_STANDARD 11)

find_package(CURL REQUIRED)

# define the library

set(library_srcs
        library/nasdaq/nasdaq.cpp
        library/yahoo/yahoo.cpp
        )

add_library(market_data_static STATIC ${library_srcs})
add_library(market_data_shared SHARED ${library_srcs})

add_library(market_data_iface INTERFACE)
target_compile_definitions(market_data_iface
        INTERFACE LIBRARY_HEADER_ONLY
        )

set(installed_srcs
        include/src/library/nasdaq/nasdaq.cpp
        include/src/library/yahoo/yahoo.cpp
        )
add_library(market_data_srcs INTERFACE)
target_sources(market_data_srcs INTERFACE
        $<INSTALL_INTERFACE:${installed_srcs}>
        )

# install and export the library

install(DIRECTORY
        library
        DESTINATION
        include/market_data
        )
install(FILES
        market_data.hpp
        api.hpp
        DESTINATION
        include/market_data
        )
install(TARGETS
        market_data_static
        market_data_shared
        market_data_iface
        market_data_srcs
        EXPORT market_data_targets
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        INCLUDES DESTINATION include
        )
install(EXPORT market_data_targets
        NAMESPACE market_data::
        DESTINATION lib/cmake/market_data
        )

install(EXPORT market_data_targets
        NAMESPACE market_data::
        DESTINATION lib/cmake/market_data
        FILE market_data-config.cmake
        )
