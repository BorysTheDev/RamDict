cmake_minimum_required (VERSION 2.8)

set (PROJECT jana)

project (${PROJECT})

#FIND_PACKAGE(Qt4 REQUIRED)
#INCLUDE(${QT_USE_FILE})
#ADD_DEFINITIONS(${QT_DEFINITIONS})

include_directories (.)
include_directories (./curves)

if(CMAKE_COMPILER_IS_GNUCC)
add_definitions (-Wall -pedantic -std=gnu++14 -O2)
endif()

file(GLOB HEADERS
    "*.h"
)

file(GLOB SOURCES
    "*.cpp"
)

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_executable (${PROJECT} ${HEADERS} ${SOURCES})
