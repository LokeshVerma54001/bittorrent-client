#include "printer.h"
#include<iostream>
#include<cctype>
#include <cstdint>

using namespace std;

bool isPrintable(const std::string& s){
    for(unsigned char c : s){
        if (c == '\n' || c == '\r' || c == '\t')
            continue;

        if (!std::isprint(c))
            return false;
    }
    return true;
}

static void printIndent(int indent){
    for(int i = 0;i<indent;i++){
        cout << "    ";
    }
}

void printBValue(const BValue &value, int indent){
    if(std::holds_alternative<std::int64_t>(value.value)){
        printIndent(indent);
        cout << "Integer: " << std::get<std::int64_t>(value.value) << endl;
        return;
    }
    if(std::holds_alternative<string>(value.value)){
        const auto& s = std::get<std::string>(value.value);

        printIndent(indent);

        if(isPrintable(s))
        {
            std::cout << "String: " << s << '\n';
        }
        else
        {
            std::cout << "Binary String (" << s.size() << " bytes)\n";
        }
    }
    if(std::holds_alternative<BList>(value.value)){
        printIndent(indent);
        cout << "List" << endl;
        const auto& list = std::get<BList>(value.value);
        for(const auto& item: list){
            printBValue(*item, indent+1);
        }
        return;
    }
    if(std::holds_alternative<BDictionary>(value.value)){
        printIndent(indent);
        cout << "Dictionary" << endl;
        const auto& dict = std::get<BDictionary>(value.value);
        for(const auto& pair: dict){
            printIndent(indent+1);
            cout <<pair.first << ":" << endl;
            printBValue(*pair.second, indent+2);
        }
        return;
    }
}
