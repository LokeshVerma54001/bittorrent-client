#pragma once

#include <string>
#include <cstdint>

class Peer{
    public:
        Peer() = default;

        Peer(const std::string& ip, std::uint16_t port);
        
        const std::string& ip() const;
        std::uint16_t port() const;
    
    private:
        std::string ip_;
        std::uint16_t port_;
};