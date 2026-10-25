cmake_minimum_required(VERSION 3.21)
project(OOP_Project)

set(CMAKE_CXX_STANDARD 17)

include_directories("C:/eigen-3.4.0")

add_executable(OOP_Project OOP_Project_Farzin.cpp)
target_link_libraries(OOP_Project PRIVATE -lstdc++fs)

