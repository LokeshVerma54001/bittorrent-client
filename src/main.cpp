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
#include "tracker_client.h"

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
    try{
        BencodeParser parser;

        auto data = readFile("ubuntu.torrent");

        auto root = parser.parse(data);

        Torrent torrent(std::move(root), std::move(data));

        PeerId peerId;
        TrackerClient tracker;
        TrackerResponse response = tracker.announce(torrent, peerId, 6881);
        std::cout << "Interval: " << response.interval() << "\n";
        std::cout << "Peers: " << response.peers().size() << "\n";
        for(const auto& peer: response.peers()){
            std::cout << peer.ip() << ":" << peer.port() << '\n';
        }
    }catch(const std::exception& e){
        std::cerr <<"Error: " << e.what() << "\n";
    }
    return 0;
}