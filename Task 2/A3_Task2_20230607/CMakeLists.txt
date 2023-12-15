cmake_minimum_required(VERSION 3.26)
project(A3_Task2_20230607)

set(CMAKE_CXX_STANDARD 17)

add_executable(A3_Task2_20230607 main.cpp
        Board.cpp
        Board.h
        Player.cpp
        Player.h
        GameManager.cpp
        GameManager.h
        RandomPlayer.cpp
        RandomPlayer.h
        X_O_Board.cpp
        X_O_Board.h)
