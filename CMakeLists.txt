cmake_minimum_required(VERSION 3.10)

# Project name and version
project(SUeksamen VERSION 1.0)

#c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Executable
add_executable(main main.cpp hero.hpp enemy.hpp displays.hpp caveFactory.hpp)
