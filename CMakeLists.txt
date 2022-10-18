cmake_minimum_required(VERSION 3.23)
project(PySub)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PySub
        interface.cpp
        interface.h
        lexanalyzer.cpp
        lexanalyzer.h
        main.cpp expEvaluator.cpp expEvaluator.h)
