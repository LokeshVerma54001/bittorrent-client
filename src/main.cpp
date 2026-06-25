#include <iostream>
#include <fstream>
#include <sstream>
#include "bencode.h"
#include "bvalue.h"
#include "printer.h"
#include "torrent.h"
#include "sha1.h"
#include "socket.h"

std::string readFile(const std::string& path){
    std::ifstream file(path, std::ios::binary); //cuz file contines binary data
    if(!file){
        throw std::runtime_error("Couldn't open the file.");
    }
    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main()
{
    BencodeParser parser;

    auto data = readFile("ubuntu.torrent");

    auto root = parser.parse(data);

    Torrent torrent(std::move(root), std::move(data));

    // printBValue(*root, 0);

    std::cout << "Name: " << torrent.name() << '\n';

    std::cout << "Tracker: "
            << torrent.announce()
            << '\n';

    std::cout << "Length: "
            << torrent.totalLength()
            << '\n';

    std::cout << "Piece Length: "
            << torrent.pieceLength()
            << '\n';
    
    std::cout << "Pieces: "
            << torrent.pieceCount()
            << '\n';
            
    std::cout << torrent.rawInfo().substr(0, 100) << std::endl;

    std::cout << sha1Hex(torrent.rawInfo()) << '\n';

    Socket socket;
    socket.connect("example.com", 80);
    std::cout << "Connected!\n";
    socket.send(
        "GET / HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "Connection: close\r\n"
        "\r\n"
    );
    std::string response = socket.receive();
    std::cout << response;
}