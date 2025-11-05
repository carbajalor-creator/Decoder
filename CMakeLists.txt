cmake_minimum_required(VERSION 3.30)
project(CS315_Decoder)

set(CMAKE_CXX_STANDARD 20)

add_executable(CS315_Decoder main.cpp
        Decoder.hpp
        Decoder.cpp)
