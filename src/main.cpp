#include <iostream>
#include <fstream>
#include <sstream>
#include "bencode.h"
#include "bvalue.h"
#include "printer.h"

std::string readFile(const std::string& path){
    std::ifstream file(path, std::ios::binary); //cuz file contines binary data
    if(!file){
        throw std::runtime_error("Couldn't open the file.");
    }
    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main()
{
    BencodeParser parser;

    auto data = readFile("ubuntu.torrent");

    auto root = parser.parse(data);

    printBValue(*root, 0);
}