cmake_minimum_required(VERSION 3.29)
project(gobang_cmd)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(gobang_cmd main.cpp
        GobangAI.cpp
        GobangAI.h
        GobangBoard.cpp
        GobangBoard.h
        GobangRuleChecker.cpp
        GobangRuleChecker.h)
