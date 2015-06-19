cmake_minimum_required(VERSION 3.2)
project(serie_5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.c)

add_executable(serie_5 ${SOURCE_FILES})