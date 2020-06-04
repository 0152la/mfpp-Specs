cmake_minimum_required(VERSION 3.13)
project(CVC4TestCompile)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT TEST_FILE)
    message(FATAL_ERROR "Missing TEST_FILE variable declaration!")
    return()
endif()

if(NOT CVC4_DIR)
    message(FATAL_ERROR "Missing CVC4_DIR variable declaration!")
    return()
endif()

find_library(CVC4_LIBS cvc4 PATHS ${CVC4_DIR}/lib)

get_filename_component(TEST_OUT ${TEST_FILE} NAME_WLE)
add_executable(${TEST_OUT}
    ${TEST_FILE})

target_include_directories(${TEST_OUT} PUBLIC ${CVC4_DIR}/include)
target_link_libraries(${TEST_OUT} PUBLIC ${CVC4_LIBS})
target_compile_options(${TEST_OUT} PRIVATE "-Wno-attributes")
target_compile_definitions(${TEST_OUT} PRIVATE EXECUTE=1)
