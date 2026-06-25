#pragma once

#include <memory>
#include <string>
#include <variant>
#include <vector>
#include <map>
#include <cstdint>

class BValue;

using BList = std::vector<std::unique_ptr<BValue>>;

using BDictionary = std::map<
                        std::string,
                        std::unique_ptr<BValue>
                    >;


class BValue
{
public:
    using Value = std::variant<
        std::int64_t,
        std::string,
        BList,
        BDictionary
    >;

    Value value;

    size_t start = 0;
    size_t end = 0;

    BValue(std::int64_t v) : value(v) {}
    BValue(const std::string& v) : value(v) {}
    BValue(BList v) : value(std::move(v)) {}
    BValue(BDictionary dict) : value(std::move(dict)) {}

    std::int64_t& asInt();
    const std::int64_t& asInt() const;

    std::string& asString();
    const std::string& asString() const;

    BList& asList();
    const BList& asList() const;

    BDictionary& asDict();
    const BDictionary& asDict() const;

    bool isInt() const;
    bool isString() const;
    bool isList() const;
    bool isDict() const;
};