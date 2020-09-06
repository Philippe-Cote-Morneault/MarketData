cmake_minimum_required(VERSION 3.3)

project(test)

#find_package(CURL REQUIRED)

#find_package(market_data REQUIRED)

add_executable(test
        test.cpp
        )

#include_directories(../src)
#link_directories(../src)

## uncomment only one of these!
target_link_libraries(test market_data_static)
#target_link_libraries(test ${CURL_LIBRARIES})
 #target_link_libraries(test market_data::market_data_shared)
 #target_link_libraries(test market_data::market_data_iface)
#target_link_libraries(test market_data::market_data_srcs)
