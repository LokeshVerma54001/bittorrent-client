#include <iostream>
#include <fstream>
#include <sstream>
#include "bencode.h"
#include "bvalue.h"
#include "printer.h"
#include "torrent.h"
#include "sha1.h"
#include "socket.h"
#include "http.h"
#include "peer_id.h"
#include "url_encode.h"
#include "tracker_response.h"

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

    TrackerResponse response(std::move(root));
    std::cout << response.interval() << '\n';
}