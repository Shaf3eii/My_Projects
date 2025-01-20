cmake_minimum_required(VERSION 3.27)
project(QuranPlaylist)

set(CMAKE_CXX_STANDARD 20)

add_executable(QuranPlaylist main.cpp
        DoublyLinkedList.h
        Surah.h
        PlayList.h
        Library.h
        Simulate.h
        AudioPlayer.h)

target_link_libraries(QuranPlaylist PRIVATE winmm)
