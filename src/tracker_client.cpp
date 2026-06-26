#include "tracker_client.h"
#include "url.h"
#include "socket.h"
#include<sstream>
#include "url_encode.h"
#include "bencode.h"

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

    request << "GET "
            << url.path()
            << "?info_hash=" << UrlEncoder::encode(torrent.infoHash())
            << "&peer_id=" << UrlEncoder::encode(peerId.value())
            << "&port=" << port
            << "&uploaded=0"
            << "&downloaded=0"
            << "&left=" << torrent.totalLength()
            << "&compact=1"
            << " HTTP/1.1\r\n";

    return request.str();
}

TrackerResponse TrackerClient::parseResponse(const std::string& response)
{
    std::size_t bodyStart = response.find("\r\n\r\n");

    if (bodyStart == std::string::npos)
    {
        throw std::runtime_error("Invalid HTTP response");
    }

    std::string body = response.substr(bodyStart + 4);

    BencodeParser parser;

    auto root = parser.parse(body);

    return TrackerResponse(std::move(root));
}