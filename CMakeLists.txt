cmake_minimum_required(VERSION 3.20)

project(BitTorrentClient)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bittorrent
    src/main.cpp
    src/bencode.cpp
    src/bvalue.cpp
    src/printer.cpp
)

target_include_directories(bittorrent
    PRIVATE
        include
)