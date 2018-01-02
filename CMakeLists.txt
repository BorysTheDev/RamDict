cmake_minimum_required (VERSION 2.8)

set (PROJECT jana)

project (${PROJECT})

include_directories (.)

if(CMAKE_COMPILER_IS_GNUCC)
add_definitions (-Wall -pedantic -std=gnu++14 -g)
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

target_link_libraries(${PROJECT} pthread boost_system)

