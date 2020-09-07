cmake_minimum_required(VERSION 3.3)

project(market_data)

cmake_policy(SET CMP0076 OLD)

set(CMAKE_CXX_STANDARD 11)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

# define the library

include_directories()

set(library_srcs
        nasdaq/nasdaq.cpp
        yahoo/yahoo.cpp
        )

add_library(market_data_static STATIC ${library_srcs})
target_include_directories(
        market_data_static
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:include>
)
target_link_libraries(market_data_static
        ${CURL_LIBRARIES})
add_library(market_data_shared SHARED ${library_srcs})
target_include_directories(
        market_data_shared
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:include>
)
target_link_libraries(market_data_shared
        ${CURL_LIBRARIES})

add_library(market_data_iface INTERFACE)
target_compile_definitions(market_data_iface
        INTERFACE LIBRARY_HEADER_ONLY
        )
target_include_directories(
        market_data_iface
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:include>
)
target_link_libraries(market_data_iface INTERFACE
        ${CURL_LIBRARIES})

set(installed_srcs
        include/market_data/nasdaq/nasdaq.cpp
        include/market_data/yahoo/yahoo.cpp
        )
add_library(market_data_srcs INTERFACE)
target_sources(market_data_srcs INTERFACE
        $<INSTALL_INTERFACE:${installed_srcs}>
        )
target_link_libraries(market_data_srcs INTERFACE
        ${CURL_LIBRARIES})

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
