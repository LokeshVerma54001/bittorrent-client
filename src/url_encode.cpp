#include "url_encode.h"

#include <iomanip>
#include <sstream>
#include <cctype>

std::string UrlEncoder::encode(const std::string& input){
    std::ostringstream out;
    for(unsigned char c : input){
        if(std::isalnum(c) || 
            c == '-' ||
            c == '_' ||
            c == '.' ||
            c == '~'){
                out << c;
            }
        else{
            out << '%'
                << std::uppercase
                << std::hex
                << std::setw(2)
                << std::setfill('0')
                << static_cast<int>(c);
            
            //restore decimal mode for future output
            out << std::dec;
        }
    }
    
    return out.str();
}
