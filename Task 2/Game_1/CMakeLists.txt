cmake_minimum_required(VERSION 3.5)
project(elkholy VERSION 0.1.0 LANGUAGES C CXX)

file( GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ) 

add_executable(elkholy ${MY_SOURCES})

target_include_directories( elkholy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )