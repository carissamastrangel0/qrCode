cmake_minimum_required(VERSION 3.26)
project(project)

set(CMAKE_CXX_STANDARD 17)

add_executable(qrCode main.cpp
        include/qrcodegen.hpp
        src/qrcodegen.cpp
        main.cpp
)



