#pragma once

#include <vector>
#include <cstdint>
#include <string>

#include "peer.h"
#include "bvalue.h"

class TrackerResponse{
    public:
        explicit TrackerResponse(std::unique_ptr<BValue> root);

        void setInterval(std::int64_t interval);
        void addPeer(const Peer& peer);

        std::int64_t interval() const;
        const std::vector<Peer>& peers() const;

    private:
        std::int64_t interval_ = 0;
        std::vector<Peer> peers_;
};