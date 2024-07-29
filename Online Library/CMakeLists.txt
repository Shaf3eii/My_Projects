cmake_minimum_required(VERSION 3.27)
project(Online_Library)

set(CMAKE_CXX_STANDARD 17)

add_executable(Online_Library main.cpp
        Book.h
        Book.cpp
        BookList.h
        User.h
        BookList.cpp
        User.cpp
        UserList.h
        UserList.cpp)
