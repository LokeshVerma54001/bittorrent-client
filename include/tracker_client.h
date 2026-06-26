#pragma once

#include <string>

#include "torrent.h"
#include "peer_id.h"
#include "tracker_response.h"

class TrackerClient{
    public:
        TrackerResponse announce(
            const Torrent& torrent,
            const PeerId& peerId,
            std::uint16_t port = 6881
        );

    private:
        std::string buildRequest(
            const Torrent& torrent,
            const PeerId& peerId,
            std::uint16_t port
        );

        TrackerResponse parseResponse(const std::string & response);
};