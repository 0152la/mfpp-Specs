cmake_minimum_required(VERSION 3.13)
project(Z3TestCompile)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT TEST_FILE)
    message(FATAL_ERROR "Missing TEST_FILE variable declaration!")
    return()
endif()

find_package(Z3 REQUIRED)

get_filename_component(TEST_OUT ${TEST_FILE} NAME_WLE)
add_executable(${TEST_OUT}
    ${TEST_FILE})
target_include_directories(${TEST_OUT} PUBLIC ${Z3_CXX_INCLUDE_DIRS})
target_link_libraries(${TEST_OUT} PUBLIC ${Z3_LIBRARIES})
target_compile_options(${TEST_OUT} PRIVATE "-Wno-attributes")
target_compile_definitions(${TEST_OUT} PRIVATE EXECUTE=1)
