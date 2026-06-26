#pragma once

#include<string>
#include <cstdint>
#include <array>

std::string sha1Hex(const std::string& data);
std::array<uint8_t, 20> sha1(const std::string& data);