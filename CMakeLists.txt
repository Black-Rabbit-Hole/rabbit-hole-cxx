cmake_minimum_required(VERSION 3.27)
project(rabbit_hole_cxx C CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")


set(SOURCE_FILES
        src/rh_Searcher.cpp
        src/rh_jvmti.cpp
        src/jmethod.cpp
        src/jmethod.h
        src/types.h
        src/jclass.cpp
        src/jclass.h
)
add_library(rabbit_hole_cxx SHARED ${SOURCE_FILES})
target_include_directories(rabbit_hole_cxx PRIVATE libs)
