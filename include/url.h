#pragma once

#include <string>

class Url{
    public:
        explicit Url(const std::string& url);

        const std::string& scheme() const;
        const std::string& host() const;
        int port() const;
        const std::string& path() const;

    private:
        std::string scheme_;
        std::string host_;
        int port_;
        std::string path_;
};