#pragma once

#include <memory>
#include <string>
#include "bvalue.h"

class Torrent{
    public:
        explicit Torrent(std::unique_ptr<BValue> root, std::string rawData);

        std::string name() const;
        std::string announce() const;
        std::int64_t totalLength() const;
        std::int64_t pieceLength() const;
        std::size_t pieceCount() const;
        const std::string& pieces() const;
        std::string rawInfo() const;
    
    private:
        std::unique_ptr<BValue> root_;
        std::string rawData_;
        
        const BDictionary& rootDict() const;
        const BDictionary& infoDict() const;
};