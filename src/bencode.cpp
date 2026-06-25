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
    size_t start = position;
    get();
    string number;
    while(peek()!='e'){
        number += get();
    }
    get();
    size_t end = position;
    auto node = std::make_unique<BValue>(std::stoll(number));
    node->start = start;
    node->end = end;
    return node;
}

std::unique_ptr<BValue> BencodeParser::parseString(){
    size_t start = position;
    auto node = make_unique<BValue>(parseRawString());
    size_t end = position;
    node->start = start;
    node->end = end;
    return node;
}

std::unique_ptr<BValue> BencodeParser::parseList(){
    size_t start = position;
    get();
    BList list;
    while(peek() != 'e'){
        list.push_back(parseValue());
    }
    get();
    size_t end = position;
    auto node = make_unique<BValue>(move(list));
    node->start = start;
    node->end = end;
    return node;
}

std::unique_ptr<BValue> BencodeParser::parseDictionary(){
    size_t start = position;
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
    size_t end = position;
    auto node = std::make_unique<BValue>(std::move(dict));
    node->start = start;
    node->end = end;
    return node;
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