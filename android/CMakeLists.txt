cmake_minimum_required(VERSION 3.4.1)

project(tuner)

set(ANDROID_STL c++_shared CACHE STRING "C++ Standard Library type")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "../shared/*.cpp")


add_library(
    tuner
    SHARED
    ${SOURCES}
)
    
target_include_directories(
    tuner
    PUBLIC
    ../shared/include
)

find_library(log-lib log)

target_link_libraries(tuner log)