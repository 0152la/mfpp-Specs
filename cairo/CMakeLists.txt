cmake_minimum_required(VERSION 3.13)
project(CairoTestSpec)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

if (LLVM_INSTALL_LOC)
    set(CMAKE_C_COMPILER ${LLVM_INSTALL_LOC}/bin/clang)
    set(CMAKE_CXX_COMPILER ${LLVM_INSTALL_LOC}bin/clang++)
    set(Clang_DIR ${LLVM_INSTALL_LOC}/lib/cmake/clang)
endif()

set(BASE_CAIRO_DIR /home/sentenced/Documents/Internships/2018_ETH/work/other_libs/cairo)

#find_package(PkgConfig REQUIRED)
#set(ENV{PKG_CONFIG_PATH}
    #"${BASE_CAIRO_DIR}/cairo-build/lib/pkgconfig/
    #:${BASE_CAIRO_DIR}/libsigc++-3.0.0")
    #:${BASE_CAIRO_DIR}/cairomm-build/lib/pkgconfig/
#pkg_check_modules(CAIRO REQUIRED cairo sigc++-3.0)

find_package(Clang REQUIRED)
#include_directories(${CLANG_INCLUDE_DIRS})

add_library(cairo_lib OBJECT
    cairo.cpp)

#target_include_directories(cairo_lib PUBLIC ${CAIRO_INCLUDE_DIRS} ${CLANG_INCLUDE_DIR})
target_include_directories(cairo_lib PUBLIC ${CLANG_INCLUDE_DIR})
target_include_directories(cairo_lib PUBLIC ${CLANG_INCLUDE_DIRS}/../lib/clang/10.0.0/include)
target_include_directories(cairo_lib PUBLIC
    /home/sentenced/Documents/Internships/2018_ETH/work/other_libs/cairo/cairomm-build/include/cairomm-1.16
    /home/sentenced/Documents/Internships/2018_ETH/work/other_libs/cairo/cairomm-build/lib/cairomm-1.16/include
    /home/sentenced/Documents/Internships/2018_ETH/work/other_libs/cairo/cairo-build/include/cairo
    /home/sentenced/Documents/Internships/2018_ETH/work/other_libs/cairo/libsigc++-3.0.0/install/include/sigc++-3.0
    /home/sentenced/Documents/Internships/2018_ETH/work/other_libs/cairo/libsigc++-3.0.0/install/lib/sigc++-3.0/include
    /usr/include/glib-2.0
    /usr/lib/glib-2.0/include
    /usr/lib/libffi-3.2.1/include
    /usr/include/pixman-1
    /usr/include/freetype2
    /usr/include/libpng16
    /usr/include/harfbuzz)
