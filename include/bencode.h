#pragma once
//tells compiler to only include this file once

#include<string>
#include "bvalue.h"

class BencodeParser{
    public:
        std::unique_ptr<BValue> parse(const std::string& input);

    private:
        std::string data;
        size_t position = 0;

        std::unique_ptr<BValue> parseValue();
        std::unique_ptr<BValue> parseInteger();
        std::unique_ptr<BValue> parseString();
        std::unique_ptr<BValue> parseList();
        std::unique_ptr<BValue> parseDictionary();

        char peek();
        void advance();
        char get();
        std::string parseRawString();
};