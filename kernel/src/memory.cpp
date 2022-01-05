#include "memory.h"

uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescSize) {
    static uint64_t memorySizeBytes = 0;
    if(memorySizeBytes > 0) return memorySizeBytes;
    
}