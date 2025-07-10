cmake_minimum_required(VERSION 3.22)
project(CalcGTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CalcLib
        ICalculator.h
        SimpleCalculator.h SimpleCalculator.cpp
        IHistory.h
        InMemoryHistory.h InMemoryHistory.cpp
)


add_subdirectory(tests)