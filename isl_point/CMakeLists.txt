cmake_minimum_required(VERSION 3.13)
project(ISLPointTestSpec)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (LLVM_INSTALL_LOC)
    set(CMAKE_C_COMPILER ${LLVM_INSTALL_LOC}/bin/clang)
    set(CMAKE_CXX_COMPILER ${LLVM_INSTALL_LOC}/bin/clang++)
    set(Clang_DIR ${LLVM_INSTALL_LOC}/lib/cmake/clang)
endif()

find_package(PkgConfig REQUIRED)
pkg_search_module(ISL REQUIRED isl)

find_package(Clang REQUIRED)
string(REGEX MATCH [0-9\.]+ CLANG_VERSION ${LLVM_PACKAGE_VERSION})

add_library(isl_point_lib OBJECT
    isl_point.cpp)
target_include_directories(isl_point_lib PUBLIC ${ISL_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})
target_include_directories(isl_point_lib PUBLIC ${CLANG_INCLUDE_DIRS}/../lib/clang/${CLANG_VERSION}/include)
target_include_directories(isl_point_lib PUBLIC ${CMAKE_SOURCE_DIR})
