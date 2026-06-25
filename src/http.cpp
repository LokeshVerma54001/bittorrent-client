#include "http.h"
#include "socket.h"

#include <sstream>

std::string HttpClient::get(const std::string& host, const std::string& path){
    Socket socket;
    socket.connect(host, 80);

    std::ostringstream request;

    request << "GET " << path << " HTTP/1.1\r\n";
    request << "Host: " << host << "\r\n";
    request << "Connection: close\r\n";
    request << "\r\n";

    socket.send(request.str());
    return socket.receive();
}