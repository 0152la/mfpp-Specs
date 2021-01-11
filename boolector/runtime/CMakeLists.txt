cmake_minimum_required(VERSION 3.13)
project(BoolectorTestSpec)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT TEST_FILE)
    message(FATAL_ERROR "Missing TEST_FILE variable declaration!")
    return()
endif()

find_package(Boolector REQUIRED)

get_filename_component(TEST_OUT ${TEST_FILE} NAME_WLE)
add_executable(${TEST_OUT}
    ${TEST_FILE})
target_link_libraries(${TEST_OUT} PUBLIC Boolector::boolector)
target_compile_options(${TEST_OUT} PRIVATE "-Wno-attributes")
target_compile_definitions(${TEST_OUT} PRIVATE EXECUTE=1)
