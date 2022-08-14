cmake_minimum_required(VERSION 3.5)

set (PROJECT netdict)
project(PROJECT LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories (.)

if(CMAKE_COMPILER_IS_GNUCC)
add_definitions (-Wall -pedantic)
endif()

file(GLOB HEADERS
    "*.h"
    "tests/*.h"
)

file(GLOB SOURCES
    "*.cpp"
    "tests/*.cpp"
)

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})


add_executable (${PROJECT} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT} pthread)

