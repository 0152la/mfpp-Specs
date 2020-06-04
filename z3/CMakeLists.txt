cmake_minimum_required(VERSION 3.13)
project(Z3TestSpec)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (LLVM_INSTALL_LOC)
    set(CMAKE_C_COMPILER ${LLVM_INSTALL_LOC}/bin/clang)
    set(CMAKE_CXX_COMPILER ${LLVM_INSTALL_LOC}/bin/clang++)
    set(Clang_DIR ${LLVM_INSTALL_LOC}/lib/cmake/clang)
endif()

set(Z3_DIR /home/sentenced/Documents/Internships/2018_ETH/work/other_libs/z3/build)
find_package(Z3 REQUIRED)
find_package(Clang REQUIRED)
string(REGEX MATCH [0-9\.]+ CLANG_VERSION ${LLVM_PACKAGE_VERSION})

add_library(z3_lib OBJECT
    z3.cpp)
target_include_directories(z3_lib PUBLIC ${CLANG_INCLUDE_DIRS} ${Z3_CXX_INCLUDE_DIRS})
target_include_directories(z3_lib PUBLIC ${CLANG_INCLUDE_DIRS}/../lib/clang/${CLANG_VERSION}/include)
