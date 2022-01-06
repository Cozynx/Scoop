#pragma once
#include <cstdint>

enum PT_FLAG {
    Present = 0,
    ReadWrite = 1,
    UserSuper = 2,
    WriteThrough = 3,
    CacheDisabled = 4,
    Accessed = 5,
    LargerPages = 7,
    Custom0 = 9,
    Custom1 = 10,
    Custom2 = 11,
    NX = 63, // only on supported system
};

struct PageDirectoryEntry {
    uint64_t Value;
    void SetFlag(PT_FLAG flag, bool enabled);
    bool GetFlag(PT_FLAG flag);
    void SetAddress(uint64_t address);
    uint64_t GetAddress();
};

struct PageTable {
    PageDirectoryEntry entries [512];
}__attribute__((aligned(0x1000)));