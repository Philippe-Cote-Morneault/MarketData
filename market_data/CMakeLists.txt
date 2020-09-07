cmake_minimum_required(VERSION 3.3)

#project(market_data)

cmake_policy(SET CMP0076 OLD)

set(CMAKE_CXX_STANDARD 11)

# Dependencies
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

# define the library
set(created_libraries "")

set(
    library_srcs
    nasdaq/nasdaq.cpp
    yahoo/yahoo.cpp
)

if (${BUILD_STATIC})
    list(APPEND created_libraries "market_data_static")
    add_library(market_data_static STATIC ${library_srcs})
    target_include_directories(
            market_data_static
            PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
            $<INSTALL_INTERFACE:include>
    )
    target_link_libraries(market_data_static
            ${CURL_LIBRARIES})
endif ()

if (${BUILD_SHARED})
    list(APPEND created_libraries "market_data_shared")
    add_library(market_data_shared SHARED ${library_srcs})
    target_include_directories(
            market_data_shared
            PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
            $<INSTALL_INTERFACE:include>
    )
    target_link_libraries(market_data_shared
            ${CURL_LIBRARIES})
endif()

if(${BUILD_HEADER})
    list(APPEND created_libraries "market_data_iface")
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
endif()


set(installed_srcs
        include/market_data/nasdaq/nasdaq.cpp
        include/market_data/yahoo/yahoo.cpp
        )

if (${BUILD_SRC})
    list(APPEND created_libraries "market_data_srcs")
    add_library(market_data_srcs INTERFACE)
    target_sources(market_data_srcs INTERFACE
            $<INSTALL_INTERFACE:${installed_srcs}>
            )
    target_link_libraries(market_data_srcs INTERFACE
            ${CURL_LIBRARIES})
endif()

# Install and export the library
install(DIRECTORY
        ${CMAKE_CURRENT_LIST_DIR}
        DESTINATION
        include/
        )
install(FILES
        market_data.hpp
        api.hpp
        DESTINATION
        include/market_data
        )
install(TARGETS
        ${created_libraries}
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
