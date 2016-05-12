cmake_minimum_required(VERSION 2.6)
project(lxml)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(LIBXML2 REQUIRED)
file(GLOB LXML_SRC "src/lxml/*.cpp")

include_directories(${LIBXML2_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(lxml ${LXML_SRC})


# Tests
enable_testing()
file(GLOB TESTS_SRC "tests/*.cpp")
add_executable(lxml_tester ${TESTS_SRC})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(lxml_tester lxml ${LIBXML2_LIBRARIES} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(lxml_tester ${EXECUTABLE_OUTPUT_PATH}/lxml_tester)
