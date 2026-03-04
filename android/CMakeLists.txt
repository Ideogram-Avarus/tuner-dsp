cmake_minimum_required(VERSION 3.4.1)

project(tuner)

set(CMAKE_CXX_STANDARD 20)

add_library(
    native_tuner_dsp
    SHARED
    ../../../../shared/NativeTunerDsp.cpp
    ../../../../shared/NativeTunerDspJSI.cpp
)

target_include_directories(
    tuner
    PRIVATE
    ../../../../shared
    ../../../../shared/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

find_package(ReactAndroid REQUIRED CONFIG)

target_link_libraries(native_tuner_dsp log)