#pragma once

#include <string>

class Socket{
    public:
        Socket();
        ~Socket();

        void connect(const std::string& host, int port);
        void send(const std::string& data);
        std::string receiveAll();

    private:
        int socketFd_;
};