#pragma once

#include <string>

class HttpClient{
    public:
        std::string getRaw(const std::string& host, const std::string& path);
        std::string getBody(const std::string& host, const std::string& path);
};