cmake_minimum_required(VERSION 3.20)
project(image_retrieval)

set(CMAKE_CXX_STANDARD 14)

include_directories(image_retrieval)

add_executable(image_retrieval
        image_retrieval/dft.cpp
        image_retrieval/dft.h
        image_retrieval/euclid.cpp
        image_retrieval/euclid.h
        image_retrieval/file.cpp
        image_retrieval/file.h
        image_retrieval/init.h
        image_retrieval/lbp.cpp
        image_retrieval/lbp.h
        image_retrieval/lbp_git.cpp
        image_retrieval/lbp_git.hpp
        image_retrieval/main.cpp)
