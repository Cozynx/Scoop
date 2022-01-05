#pragma once
#include <cstdint>

const char* to_string(uint64_t value);
const char* to_string(int64_t value);
const char* to_string(double value, uint8_t decimal_places);
const char* to_string(double value);
const char* to_hstring(uint64_t value);
const char* to_hstring(uint32_t value);
const char* to_hstring(uint16_t value);
const char* to_hstring(uint8_t value);