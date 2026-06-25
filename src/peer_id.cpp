#include "peer_id.h"

#include <random>

//generates a random bittorrent id for the BT client
std::string PeerId::generate(){
    std::string id = "-BC0001-";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 9);
    while(id.size() < 20){
        id += static_cast<char>('0' + dist(gen));
    }
    return id;
}