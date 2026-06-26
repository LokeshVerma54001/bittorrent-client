#include "tracker_client.h"
#include "url.h"
// #include "socket.h"
#include "tls_socket.h"
#include<sstream>
#include "url_encode.h"
#include "bencode.h"
#include <iostream>

TrackerResponse TrackerClient::announce(const Torrent& torrent, const PeerId& peerId, std::uint16_t port){
    std::cout << "1. Parsing URL\n";
    Url url(torrent.announce());

    std::cout << "2. Creating socket\n";
    TlsSocket socket;

    std::cout << "3. Connecting...\n";
    socket.connect(url.host(), url.port());

    std::cout << "4. Building request\n";
    std::string request = buildRequest(torrent, peerId, port);

    std::cout << "===== REQUEST =====\n";
    std::cout << request;
    std::cout << "===================\n";

    std::cout << "5. Sending request\n";
    socket.send(request);

    std::cout << "6. Waiting for response\n";
    std::string response = socket.receiveAll();

    std::cout << "7. Response received\n";
    std::cout << "===== RESPONSE =====\n";
    std::cout << response << '\n';
    std::cout << "====================\n";
    return parseResponse(response);
}

std::string TrackerClient::buildRequest(
    const Torrent& torrent,
    const PeerId& peerId,
    std::uint16_t port)
{
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

    request << "Host: " << url.host() << "\r\n";

    request << "Connection: close\r\n";

    request << "\r\n";

    return request.str();
}

TrackerResponse TrackerClient::parseResponse(const std::string& response)
{
    size_t bodyPos = response.find("\r\n\r\n");
    if (bodyPos == std::string::npos)
    {
        throw std::runtime_error("Invalid HTTP response");
    }

    std::string body = response.substr(bodyPos + 4);

    BencodeParser parser;
    auto root = parser.parse(body);

    return TrackerResponse(std::move(root));
}