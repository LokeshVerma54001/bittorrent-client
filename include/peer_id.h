#pragma once

#include <string>

class PeerId{
    public:
        PeerId();
        const std::string& value() const;

    private:
        std::string id_;
        std::string generate();
};