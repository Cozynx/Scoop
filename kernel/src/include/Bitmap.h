#pragma once
#include <cstddef>
#include <cstdint>

class Bitmap{
public:
    size_t Size;
    uint8_t* Buffer;
    bool Get(uint64_t index);
    bool operator[](uint64_t index);
    bool Set(uint64_t index, bool value);
};