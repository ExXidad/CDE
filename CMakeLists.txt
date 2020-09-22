cmake_minimum_required(VERSION 3.15)
project(CDE)

set(CMAKE_CXX_STANDARD 17)

add_executable(CDE main.cpp Domain.cpp Domain.h Solver.cpp Solver.h BoundingRect.cpp BoundingRect.h)