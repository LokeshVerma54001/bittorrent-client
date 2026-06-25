#include "peer.h"

Peer::Peer(const std::string& ip, std::uint16_t port) : ip_(ip), port_(port){}

const std::string& Peer::ip() const{
    return ip_;
}

std::uint16_t Peer::port() const{
    return port_;
}