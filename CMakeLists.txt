cmake_minimum_required(VERSION 3.20)

project(BitTorrentClient)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)

add_executable(bittorrent
    src/main.cpp
    src/bencode.cpp
    src/bvalue.cpp
    src/printer.cpp
    src/torrent.cpp
    src/sha1.cpp
    src/socket.cpp
    src/http.cpp
    src/url.cpp
    src/peer_id.cpp
    src/url_encode.cpp
    src/peer.cpp
    src/tracker_response.cpp
    src/tracker_client.cpp
)

target_include_directories(bittorrent
    PRIVATE
        include
)

target_link_libraries(bittorrent
    PRIVATE
        OpenSSL::Crypto
)