#include "url.h"

#include<stdexcept>

Url::Url(const std::string& url){

    port_ = 80;    //default port
    size_t schemeEnd = url.find("://");
    if(schemeEnd == std::string::npos){
        throw std::runtime_error("Invalid Url");
    }
    //Extract scheme
    scheme_ = url.substr(0, schemeEnd);
    //sets default port based on scheme
    if(scheme_ == "https"){
        port_ = 443;
    }
    //host begins after "://"
    size_t hostStart = schemeEnd + 3;
    //finds where the path starts
    size_t pathStart = url.find('/', hostStart);
    std::string hostPort;
    if(pathStart == std::string::npos){
        hostPort = url.substr(hostStart);
        path_ = "/";
    }else{
        hostPort = url.substr(hostStart, pathStart - hostStart);
        path_ = url.substr(pathStart);
    }
    //look for an explicit port
    size_t colonPos = hostPort.find(':');
    if(colonPos == std::string::npos){
        host_ = hostPort;
    }
    else{
        host_ = hostPort.substr(0, colonPos);
        std::string portString = hostPort.substr(colonPos + 1);
        port_ = std::stoi(portString);
    }
}

const std::string& Url::scheme() const{
    return scheme_;
}

const std::string& Url::host() const {
    return host_;
}

int Url::port() const{
    return port_;
}

const std::string& Url::path() const{
    return path_;
}