cmake_minimum_required(VERSION 3.27)
project(Contacts_Book_App)

set(CMAKE_CXX_STANDARD 20)

add_executable(Contacts_Book_App main.cpp
        Address.h
        Person.h
        Vector.h
        ContactsBook.h)
