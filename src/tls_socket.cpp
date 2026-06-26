#include "tls_socket.h"

#include <openssl/ssl.h>
#include <openssl/err.h>

#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <iostream>

TlsSocket::TlsSocket(){
    SSL_library_init();
    SSL_load_error_strings();

    ctx_ = SSL_CTX_new(TLS_client_method());

    if(!ctx_){
        throw std::runtime_error("Failed to create SSL context.");
    }
    ssl_ = nullptr;
    socketFd_ = -1;
}

TlsSocket::~TlsSocket(){
    if(ssl_)
        SSL_free(ssl_);
    if(socketFd_ != -1)
        close(socketFd_);
    if(ctx_)
        SSL_CTX_free(ctx_);
}

void TlsSocket::connect(const std::string& host, int port){
    addrinfo hints{};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    addrinfo* result = nullptr;
    int status = getaddrinfo(
        host.c_str(),
        std::to_string(port).c_str(),
        &hints,
        &result
    );
    if(status != 0)
        throw std::runtime_error(gai_strerror(status));
    addrinfo* rp;
    for(rp = result; rp!=nullptr;rp = rp->ai_next){
        socketFd_ = socket(
            rp->ai_family,
            rp->ai_socktype,
            rp->ai_protocol
        );
        if(socketFd_ == -1) continue;
        if(::connect(socketFd_, rp->ai_addr, rp->ai_addrlen) == 0) break;
        close(socketFd_);
        socketFd_ = -1;
    }
    freeaddrinfo(result);
    if(socketFd_ == -1)
        throw std::runtime_error("TCP connect failed.");
    ssl_ = SSL_new(ctx_);
    if(!ssl_)
        throw std:: runtime_error("SSL_new failed");
    SSL_set_fd(ssl_, socketFd_);
    SSL_set_tlsext_host_name(ssl_, host.c_str());
    if(SSL_connect(ssl_) <= 0){
        ERR_print_errors_fp(stderr);
        throw std::runtime_error("TLS handshake failed.");
    }
}

void TlsSocket::send(const std::string& data)
{
    int written = SSL_write(
        ssl_,
        data.data(),
        static_cast<int>(data.size())
    );

    std::cout << "SSL_write = " << written << '\n';

    if (written <= 0)
    {
        ERR_print_errors_fp(stderr);
        throw std::runtime_error("SSL_write failed");
    }
}

std::string TlsSocket::receiveAll()
{
    std::string response;
    char buffer[4096];

    while (true)
    {
        int bytes = SSL_read(ssl_, buffer, sizeof(buffer));

        if (bytes > 0)
        {
            response.append(buffer, bytes);
            continue;
        }

        int err = SSL_get_error(ssl_, bytes);

        std::cout << "SSL_read error = " << err << '\n';

        if (err == SSL_ERROR_ZERO_RETURN)
            break;

        if (err == SSL_ERROR_WANT_READ)
            continue;

        if (err == SSL_ERROR_WANT_WRITE)
            continue;

        ERR_print_errors_fp(stderr);
        break;
    }

    return response;
}