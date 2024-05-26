cmake_minimum_required(VERSION 3.5)
project(elkholy VERSION 0.1.0 LANGUAGES C CXX)

file( GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ) 

add_executable(elkholy ${MY_SOURCES})

target_include_directories( elkholy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )

set(CMAKE_CXX_STANDARD 14)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/Project 3/SFML/include/SFML)
target_link_libraries(elkholy sfml-system sfml-window sfml-graphics sfml-audio)
