cmake_minimum_required(VERSION 3.13)
project(CVC5TestCompile)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT TEST_FILE)
    message(FATAL_ERROR "Missing TEST_FILE variable declaration!")
endif()

if(NOT DEFINED ENV{CVC5_INSTALL_LOC})
    message(FATAL_ERROR "Missing CVC4_INSTALL_LOC env variable declaration!")
endif()

find_library(CVC5_LIBS cvc5 PATHS $ENV{CVC5_INSTALL_LOC}/lib)

get_filename_component(TEST_OUT ${TEST_FILE} NAME_WLE)
add_executable(${TEST_OUT}
    ${TEST_FILE})

target_include_directories(${TEST_OUT} PUBLIC $ENV{CVC5_INSTALL_LOC}/include)
target_include_directories(${TEST_OUT} PUBLIC ${CMAKE_SOURCE_DIR}/..)
target_link_libraries(${TEST_OUT} PUBLIC ${CVC5_LIBS})
target_compile_options(${TEST_OUT} PRIVATE "-Wno-attributes")
target_compile_definitions(${TEST_OUT} PRIVATE EXECUTE=1)
