# Adapted from: https://www.youtube.com/watch?v=UH6F6ypdYbw
#               https://www.youtube.com/watch?v=pxJoVRfpRPE

cmake_minimum_required(VERSION 3.13)

project(homework_01 VERSION 0.0.1
                    DESCRIPTION "Sparse matrix compression algorithms implementation"
                    LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

add_library(cxx_setup INTERFACE)
target_compile_options(cxx_setup INTERFACE -Wall -Wpedantic -Wextra -O2 -Wsuggest-override)
target_compile_features(cxx_setup INTERFACE cxx_std_17)

include(cmake/UpdateSubmodules.cmake)

include(CTest)

add_subdirectory("${PROJECT_NAME}")
add_subdirectory(examples)
add_subdirectory(external)

if(CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
add_subdirectory(docs)
endif()