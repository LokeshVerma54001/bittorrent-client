#include "socket.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>


Socket::Socket() : socketFd_(-1){} //when not connected linux returns -1 for invalid sockets

Socket::~Socket(){
    if(socketFd_ != -1){
        close(socketFd_);
    }
}

void Socket::connect(const std::string& host, int port){
    addrinfo hints{}; //zero initializes every field
    hints.ai_family = AF_INET; // supports ipv4 addresses
    hints.ai_socktype = SOCK_STREAM; //meaning uses TCP connection
    std::string portString = std::to_string(port);
    addrinfo* result = nullptr;
    int status = getaddrinfo(
                    host.c_str(),
                    portString.c_str(),
                    &hints,
                    &result
    ); //looks up dns and returns list of IPs
    if(status != 0){
        throw std::runtime_error(
            gai_strerror(status)
        );
    }
    //treverse list of IPs
    for(addrinfo* current = result;current != nullptr; current = current->ai_next){
        socketFd_ = socket(
            current->ai_family,
            current->ai_socktype,
            current->ai_protocol
        );
        if(socketFd_ == -1) continue; //checks for faliues
        //actually connect
        if(::connect(
                socketFd_,
                current->ai_addr,
                current->ai_addrlen
        ) == 0){
            break;
        }
        
        close(socketFd_);
        socketFd_ = -1;
    }

    freeaddrinfo(result);
    if(socketFd_ == -1){
        throw std::runtime_error("Failed to connect.");
    }
}

void Socket::send(const std::string& data){
    ssize_t bytesSent = ::send(
                            socketFd_,
                            data.data(),
                            data.size(),
                            0
    );
    if(bytesSent == -1){
        throw std::runtime_error("Failed to send data");
    }
}

std::string Socket::receive(){
    char buffer[4096]; // common page size and large enought for many reads
    std::string response;
    while(true){
        ssize_t bytesReceived = recv(
                                socketFd_,
                                buffer,
                                sizeof(buffer),
                                0
        );
        if(bytesReceived > 0){
            response.append(buffer, bytesReceived);
        }else if(bytesReceived == 0) break;
        else throw std::runtime_error("Receive failed.");
    }
    return response;
}