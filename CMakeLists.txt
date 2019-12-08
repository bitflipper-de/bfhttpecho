cmake_minimum_required(VERSION 2.8)

project(bfhttpecho)

if(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")
    add_definitions(/W2)
    add_definitions(/WX)
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()

set(CMAKE_CXX_STANDARD 14)

## Dependencies

find_package(Qt5 COMPONENTS Core REQUIRED)

## Configuration

include(config/version.cmake)
include(config/default.cmake)

configure_file(config/bfhttpecho.h.in bfhttpecho.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})


## Code

add_subdirectory(app)

## Tests

enable_testing()

if (BFLIB_BUILD_TESTS)
    add_subdirectory(test)
endif()
