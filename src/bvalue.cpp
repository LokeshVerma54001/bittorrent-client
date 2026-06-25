#include "bvalue.h"

std::int64_t& BValue::asInt(){
    return std::get<std::int64_t>(value);
}

const std::int64_t& BValue::asInt() const{
    return std::get<std::int64_t>(value);
}

std::string& BValue::asString(){
    return std::get<std::string>(value);
}

const std::string& BValue::asString() const{
    return std::get<std::string>(value);
}

BList& BValue::asList(){
    return std::get<BList>(value);
}

const BList& BValue::asList() const{
    return std::get<BList>(value);
}

BDictionary& BValue::asDict(){
    return std::get<BDictionary>(value);
}

const BDictionary& BValue::asDict() const{
    return std::get<BDictionary>(value);
}

bool BValue::isInt() const{
    return std::holds_alternative<std::int64_t>(value);
}

bool BValue::isString() const{
    return std::holds_alternative<std::string>(value);
}

bool BValue::isList() const{
    return std::holds_alternative<BList>(value);
}

bool BValue::isDict() const{
    return std::holds_alternative<BDictionary>(value);
}