cmake_minimum_required(VERSION 3.4.1)

project(tuner)

set(CMAKE_CXX_STANDARD 20)

add_library(
    tuner
    SHARED
    ../shared/NativeTunerDsp.cpp
    ../shared/NativeTunerDspJSI.cpp
)

target_include_directories(
    tuner
    PRIVATE
    ../shared
    ../shared/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

find_library(log-lib log)

target_link_libraries(tuner log)