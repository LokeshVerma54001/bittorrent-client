#include "tracker_response.h"

TrackerResponse::TrackerResponse(std::unique_ptr<BValue> root){
    const auto& dict = root->asDict();

    interval_ = static_cast<std::uint32_t>(dict.at("interval")->asInt());

    //decoding peers
    const std::string& peers = dict.at("peers")->asString();
    for(size_t i = 0;i+5<peers.size();i+=6){
        uint8_t a = static_cast<uint8_t>(peers[i]);
        uint8_t b = static_cast<uint8_t>(peers[i + 1]);
        uint8_t c = static_cast<uint8_t>(peers[i + 2]);
        uint8_t d = static_cast<uint8_t>(peers[i + 3]);

        std::string ip =
            std::to_string(a) + "." +
            std::to_string(b) + "." +
            std::to_string(c) + "." +
            std::to_string(d);

        uint16_t port =
            (static_cast<uint8_t>(peers[i + 4]) << 8) |
            static_cast<uint8_t>(peers[i + 5]);

        addPeer(Peer(ip, port));
    }
}

void TrackerResponse::setInterval(std::int64_t interval){
    interval_ = interval;
}

void TrackerResponse::addPeer(const Peer& peer){
    peers_.push_back(peer);
}

std::int64_t TrackerResponse::interval() const{
    return interval_;
}

const std::vector<Peer>& TrackerResponse::peers() const{
    return peers_;
}