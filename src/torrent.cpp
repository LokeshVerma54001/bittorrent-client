#include "torrent.h"
#include "sha1.h"

Torrent::Torrent(std::unique_ptr<BValue> root, std::string rawData) : root_(std::move(root)), rawData_(std::move(rawData)) {}

const BDictionary& Torrent::rootDict() const{
    return root_->asDict();
}

const BDictionary& Torrent::infoDict() const{
    return rootDict().at("info")->asDict();
}

std::string Torrent::name() const{
    return infoDict().at("name")->asString();
}

std::string Torrent::announce() const{
    return rootDict().at("announce")->asString();
}

std::int64_t Torrent::totalLength() const{
    return infoDict().at("length")->asInt();
}

std::int64_t Torrent::pieceLength() const{
    return infoDict().at("piece length")->asInt();
}

const std::string& Torrent::pieces() const{
    return infoDict().at("pieces")->asString();
}

std::size_t Torrent::pieceCount() const{
    return pieces().size() / 20;
}

std::string Torrent::rawInfo() const{
    const BValue& info = *rootDict().at("info");
    return rawData_.substr(info.start, info.end - info.start);
}

std::string Torrent::infoHash() const{
    return sha1(rawInfo());
}