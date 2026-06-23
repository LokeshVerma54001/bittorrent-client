#include "bencode.h"
#include<iostream>

using namespace std;

std::unique_ptr<BValue> BencodeParser::parse(const string& input){
    data = input;
    position = 0;
    return parseValue();
}

std::unique_ptr<BValue> BencodeParser::parseValue(){
    char c = peek();

    if (c == 'i')
        return parseInteger();

    if (c == 'l')
        return parseList();

    if (c == 'd')
        return parseDictionary();

    if (std::isdigit(static_cast<unsigned char>(c)))
        return parseString();

    throw std::runtime_error(
        std::string("Unexpected character: ") + c
    );
}

std::unique_ptr<BValue> BencodeParser::parseInteger(){
    get();
    string number;
    while(peek()!='e'){
        number += get();
    }
    get();
    return make_unique<BValue>(std::stoll(number));
}

std::unique_ptr<BValue> BencodeParser::parseString(){
    return make_unique<BValue>(parseRawString());
}

std::unique_ptr<BValue> BencodeParser::parseList(){
    get();
    BList list;
    while(peek() != 'e'){
        list.push_back(parseValue());
    }
    get();
    return make_unique<BValue>(move(list));
}

std::unique_ptr<BValue> BencodeParser::parseDictionary(){
    get();
    BDictionary dict;
    while(peek() != 'e'){
        auto key = parseRawString();
        auto value = parseValue();
        dict.emplace(
            key,
            std::move(value)
        );
    }
    get();
    return std::make_unique<BValue>(std::move(dict));
}

char BencodeParser::peek(){
    if(position >= data.size()){
        throw std::runtime_error("Unexpected end of input");
    }
    return data[position];
}

void BencodeParser::advance(){
    position++;
}

char BencodeParser::get(){
    if(position >= data.size()){
        throw std::runtime_error("Unexpected end of input");
    }
    return data[position++];
}

std::string BencodeParser::parseRawString(){
    string lengthString;
    while(peek()!=':'){
        lengthString += get();
    }
    get();
    int length = std::stoi(lengthString);
    string value;
    for(int i = 0;i<length;i++){
        value += get();
    }
    return value;
}