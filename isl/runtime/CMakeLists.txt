cmake_minimum_required(VERSION 3.13)
project(ISLTestCompile)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT TEST_FILE)
    message(FATAL_ERROR "Missing TEST_FILE variable declaration!")
    return()
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(ISL REQUIRED isl)

if(NOT ISL_FOUND)
    message(FATAL_ERROR "Did not find ISL pkg_config module!")
    return()
endif()


get_filename_component(TEST_OUT ${TEST_FILE} NAME_WLE)
add_executable(${TEST_OUT}
    ${TEST_FILE})
target_include_directories(${TEST_OUT} PUBLIC ${ISL_INCLUDE_DIRS})
target_link_libraries(${TEST_OUT} PUBLIC ${ISL_LIBRARIES})
target_compile_options(${TEST_OUT} PRIVATE "-Wno-attributes")
target_compile_definitions(${TEST_OUT} PRIVATE EXECUTE=1)
