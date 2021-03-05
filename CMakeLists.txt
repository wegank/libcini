cmake_minimum_required(VERSION 3.16)
project(cini C)

option(build_examples "Build examples" OFF)

set(CMAKE_C_STANDARD 11)

add_subdirectory(src)

if (build_examples)
    add_subdirectory(examples)
endif ()

include(cmake/packaging.cmake)
include(CPack)
