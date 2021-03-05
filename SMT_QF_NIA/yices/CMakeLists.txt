cmake_minimum_required(VERSION 3.13)
project(YicesTestSpec)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (LLVM_INSTALL_LOC)
    set(CMAKE_C_COMPILER ${LLVM_INSTALL_LOC}/bin/clang)
    set(CMAKE_CXX_COMPILER ${LLVM_INSTALL_LOC}/bin/clang++)
    set(Clang_DIR ${LLVM_INSTALL_LOC}/lib/cmake/clang)
endif()

if(NOT DEFINED ENV{YICES_INSTALL_LOC})
    message(FATAL_ERROR "Missing YICES_INSTALL_LOC env variable declaration!")
endif()

find_package(Clang REQUIRED)
string(REGEX MATCH [0-9\.]+ CLANG_VERSION ${LLVM_PACKAGE_VERSION})

add_library(yices_lib OBJECT
    yices.cpp)
target_include_directories(yices_lib PUBLIC ${CLANG_INCLUDE_DIRS})
target_include_directories(yices_lib PUBLIC ${CLANG_INCLUDE_DIRS}/../lib/clang/${CLANG_VERSION}/include)
target_include_directories(yices_lib PUBLIC $ENV{YICES_INSTALL_LOC}/include)
target_include_directories(yices_lib PUBLIC ${CMAKE_SOURCE_DIR})
