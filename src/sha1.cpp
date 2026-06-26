#include "sha1.h"

#include <openssl/sha.h>
#include <iomanip>
#include <sstream>

std::string sha1Hex(const std::string& data){

    auto binary = sha1(data);
    static const char* digits = "0123456789abcdef";
    std::string hex;
    for(unsigned char c : binary){
        hex += digits[c>>4];
        hex += digits[c & 0x0F];
    }
    return hex;
}

std::string sha1(const std::string& data){
    unsigned char hash[20];
    return std::string(reinterpret_cast<char*>(hash), 20);
}