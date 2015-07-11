cmake_minimum_required (VERSION 2.6)
project (GraphLib)

add_executable(graphlibtest src/test.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -lX11")