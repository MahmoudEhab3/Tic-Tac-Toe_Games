cmake_minimum_required(VERSION 3.25)
project(connect4)

set(CMAKE_CXX_STANDARD 17)

add_executable(connect4 main.cpp connect4.cpp connect4.h BoardGame_Classes.hpp)
