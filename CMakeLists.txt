cmake_minimum_required(VERSION 3.26)
project(project)

set(CMAKE_CXX_STANDARD 17)

add_executable(qrCode main.cpp
        qrcodegen/cpp/qrcodegen.hpp
        qrcodegen/cpp/qrcodegen.cpp
        qrcodegen/cpp/QrCodeGeneratorDemo.cpp
        main.cpp
)

