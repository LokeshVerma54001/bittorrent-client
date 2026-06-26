#pragma once

#include <string>

struct ssl_st;
struct ssl_ctx_st;

//transport layer secure socket

class TlsSocket{
    public:
        TlsSocket();
        ~TlsSocket();

        void connect(const std::string& host, int port);
        void send(const std::string& data);
        std::string receiveAll();

    private:
        int socketFd_;

        ssl_ctx_st* ctx_;
        ssl_st* ssl_;
};