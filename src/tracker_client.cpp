#include "tracker_client.h"
#include "url.h"
#include "socket.h"
#include<sstream>
#include "url_encode.h"

TrackerResponse TrackerClient::announce(const Torrent& torrent, const PeerId& peerId, std::uint16_t port){
    Url url(torrent.announce());
    Socket socket;
    socket.connect(url.host(), url.port());
    std::string request = buildRequest(torrent, peerId, port);
    socket.send(request);
    std::string response = socket.receiveAll();
    return parseResponse(response);
}

std::string TrackerClient::buildRequest(const Torrent& torrent, const PeerId& peerId, std::uint16_t port){
    Url url(torrent.announce());

    std::ostringstream request;

    request << "GET " << url.path();

    request << "?info_hash=" << UrlEncoder::encode(torrent.infoHash());

    request << "&peer_id=" << UrlEncoder::encode(peerId.value());

    request << "&port=" << port;

    request << "&uploaded=0";
    request << "&downloaded=0";
    request << "&left=" << torrent.totalLength();
    request << "&compact=1";

    request << " HTTP/1.1\r\n";

    request << "Host: " << url.host() << "\r\n";

    request << "Connection: close\r\n";

    request << "\r\n";

    return request.str();
}

TrackerResponse TrackerClient::parseResponse(const std::string& response){
    TrackerResponse trackerResponse;
    return trackerResponse;
}