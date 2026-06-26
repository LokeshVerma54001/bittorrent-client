#include "http.h"
#include "socket.h"

#include <sstream>

std::string HttpClient::getRaw(const std::string& host, const std::string& path){
    Socket socket;
    socket.connect(host, 80);

    std::ostringstream request;

    request << "GET " << path << " HTTP/1.1\r\n";
    request << "Host: " << host << "\r\n";
    request << "Connection: close\r\n";
    request << "\r\n";

    socket.send(request.str());
    return socket.receiveAll();
}

std::string HttpClient::getBody(const std::string& host, const std::string& path){
    std::string response = getRaw(host, path);
    ssize_t pos = response.find("\r\n\r\n");
    if(pos == std::string::npos){
        throw std::runtime_error(
            "Invalid HTTP response."
        );
    }
    return response.substr(pos + 4);
}