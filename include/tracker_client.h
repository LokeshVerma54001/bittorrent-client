#pragma once

#include <vector>
#include <cstdint>

#include "peer.h"

class TrackerResponse{
    public:
        void setInterval(std::int64_t interval);
        void addPeer(const Peer& peer);

        std::int64_t interval() const;
        const std::vector<Peer>& peers() const;

    private:
        std::int64_t interval_ = 0;
        std::vector<Peer> peers_;
};