#pragma once

#include "efiMemory.h"
#include <cstdint>
#include "bitmap.h"
#include "memory.h"

class PageFrameAllocator {
public:
    void ReadEfiMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize);
    Bitmap PageBitmap;

private:
    void InitBitmap(size_t bitmapSize, void* bufferAddress);
};