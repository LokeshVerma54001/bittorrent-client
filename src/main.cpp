#include "url.h"
#include <iostream>

int main()
{
    Url url1("https://torrent.ubuntu.com/announce");
    Url url2("http://example.com");
    Url url3("http://localhost:8080/index.html");

    auto print = [](const Url& url)
    {
        std::cout << "Scheme : " << url.scheme() << '\n';
        std::cout << "Host   : " << url.host() << '\n';
        std::cout << "Port   : " << url.port() << '\n';
        std::cout << "Path   : " << url.path() << '\n';
        std::cout << '\n';
    };

    print(url1);
    print(url2);
    print(url3);
}