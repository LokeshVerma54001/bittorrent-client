#include "sha1.h"

#include <openssl/sha.h>
#include <iomanip>
#include <sstream>

std::string sha1Hex(const std::string& data){

    unsigned char hash[SHA_DIGEST_LENGTH]; //20

    SHA1(
        reinterpret_cast<const unsigned char*>(data.data()),
        data.size(),
        hash
    );

    std::ostringstream out;

    for(int i = 0;i<SHA_DIGEST_LENGTH;i++){
        out << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return out.str();
}
