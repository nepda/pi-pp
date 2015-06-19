cmake_minimum_required(VERSION 3.2)
project(serie_6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    aufgabe1.txt
    serie_6.pdf)

add_executable(serie_6 ${SOURCE_FILES})