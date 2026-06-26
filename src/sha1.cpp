#include "sha1.h"

#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <array>

std::string sha1Hex(const std::string& data)
{
    auto hash = sha1(data);

    static const char* digits = "0123456789abcdef";

    std::string hex;

    for (uint8_t c : hash)
    {
        hex += digits[c >> 4];
        hex += digits[c & 0x0F];
    }

    return hex;
}

std::array<uint8_t,20> sha1(const std::string& data)
{
    std::array<uint8_t,20> hash;

    SHA1(
        reinterpret_cast<const unsigned char*>(data.data()),
        data.size(),
        hash.data()
    );

    return hash;
}