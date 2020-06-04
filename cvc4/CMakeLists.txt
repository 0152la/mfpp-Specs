cmake_minimum_required(VERSION 3.13)
project(CVCTestSpec)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (LLVM_INSTALL_LOC)
    set(CMAKE_C_COMPILER ${LLVM_INSTALL_LOC}/bin/clang)
    set(CMAKE_CXX_COMPILER ${LLVM_INSTALL_LOC}/bin/clang++)
    set(Clang_DIR ${LLVM_INSTALL_LOC}/lib/cmake/clang)
endif()

if (NOT CVC4_INSTALL_LOC)
    message(FATAL_ERROR "Missing CVC4_INSTALL_LOC variable declaration!")
    return()
endif()

find_package(Clang REQUIRED)
string(REGEX MATCH [0-9\.]+ CLANG_VERSION ${LLVM_PACKAGE_VERSION})

add_library(cvc4_lib OBJECT
    cvc4.cpp)
target_include_directories(cvc4_lib PUBLIC ${CLANG_INCLUDE_DIRS})
target_include_directories(cvc4_lib PUBLIC ${CLANG_INCLUDE_DIRS}/../lib/clang/${CLANG_VERSION}/include)
target_include_directories(cvc4_lib PUBLIC ${CVC4_INSTALL_LOC}/include/cvc4)
target_include_directories(cvc4_lib PUBLIC ${CVC4_INSTALL_LOC}/include/)
