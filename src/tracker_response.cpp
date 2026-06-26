#include "tracker_response.h"

TrackerResponse::TrackerResponse(std::unique_ptr<BValue> root){
    const auto& dict = root->asDict();

    interval_ = static_cast<std::uint32_t>(dict.at("interval")->asInt());
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