#include "bvalue.h"

std::int64_t& BValue::asInt(){
    return std::get<std::int64_t>(value);
}

std::string& BValue::asString(){
    return std::get<std::string>(value);
}

BList& BValue::asList(){
    return std::get<BList>(value);
}

BDictionary& BValue::asDict(){
    return std::get<BDictionary>(value);
}