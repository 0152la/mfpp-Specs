cmake_minimum_required(VERSION 3.13)
project(YicesTestCompile)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT TEST_FILE)
    message(FATAL_ERROR "Missing TEST_FILE variable declaration!")
    return()
endif()

if(NOT DEFINED ENV{YICES_INSTALL_LOC})
    message(FATAL_ERROR "Missing YICES_INSTALL_LOC env variable declaration!")
endif()

find_library(YICES_LIBS yices PATHS $ENV{YICES_INSTALL_LOC}/lib)

set(THIRD_PARTY_INSTALL_LOC /home/sentenced/Documents/Internships/2018_ETH/work/other_libs/yices2/third_party/install)
find_library(CUDD_LIBS cudd PATHS ${THIRD_PARTY_INSTALL_LOC}/lib)
find_library(GMP_LIBS gmp PATHS ${THIRD_PARTY_INSTALL_LOC}/lib)
find_library(LIBPOLY_LIBS poly PATHS ${THIRD_PARTY_INSTALL_LOC}/lib)

get_filename_component(TEST_OUT ${TEST_FILE} NAME_WLE)
add_executable(${TEST_OUT}
    ${TEST_FILE})

target_include_directories(${TEST_OUT} PUBLIC $ENV{YICES_INSTALL_LOC}/include)
target_include_directories(${TEST_OUT} PUBLIC ${CMAKE_SOURCE_DIR}/../..)
target_link_libraries(${TEST_OUT} PUBLIC ${YICES_LIBS})
target_link_libraries(${TEST_OUT} PUBLIC ${CUDD_LIBS})
target_link_libraries(${TEST_OUT} PUBLIC ${GMP_LIBS})
target_link_libraries(${TEST_OUT} PUBLIC ${LIBPOLY_LIBS})
target_link_libraries(${TEST_OUT} PUBLIC gcov)
target_compile_options(${TEST_OUT} PRIVATE "-Wno-attributes")
target_compile_definitions(${TEST_OUT} PRIVATE EXECUTE=1)
set_target_properties(${TEST_OUT} PROPERTIES LINK_FLAGS "-lgcov")
