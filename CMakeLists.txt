cmake_minimum_required (VERSION 3.1) 

project(MainProject VERSION 1.0.0 DESCRIPTION "MainProject" LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(LIB_HEADERS Curves.h)
set(LIB_SOURCES Curves.cpp)

add_library(curveslib SHARED ${LIB_HEADERS} ${LIB_SOURCES})
target_include_directories(curveslib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(MainProject main.cpp)

target_link_libraries(MainProject PUBLIC curveslib)