#include "../../includes/PageFrameAllocator.h"

uint64_t freeMemory;
uint64_t reservedMemory;
uint64_t usedMemory;
bool Initialized = false;

void PageFrameAllocator::ReadEfiMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize) {
    if(Initialized) return;

    Initialized = true;
    uint64_t mMapEnteries = mMapSize / mMapDescSize;

    void* largestFreeMemSeg = NULL;
    size_t largestFreeMemSegSize = 0;

    for(int i = 0; i < mMapEnteries; i++) {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((int64_t)mMap + (i * mMapDescSize));
        if(desc->type == 7){ // type = EfiConventionalMemory
            if(desc->numPages * 4096 > largestFreeMemSegSize) {
                largestFreeMemSeg = desc->physAddr;
                largestFreeMemSegSize = desc->numPages * 4096;
            }
        }
    }

    uint64_t memorySize = GetMemorySize(mMap, mMapEnteries, mMapDescSize);
    freeMemory = memorySize;
    uint64_t bitmapSize = memorySize / 4096 / 8 + 1;

    // Initialize bitmap
    InitBitmap(bitmapSize, largestFreeMemSeg);

    // lock pages of bitmap
    // reserve pages of unusable/reserved bitmap
}

void PageFrameAllocator::InitBitmap(size_t bitmapSize, void* bufferAddress) {
    PageBitmap.Size = bitmapSize;
    PageBitmap.Buffer = (uint8_t*)bufferAddress;
    for(int i = 0; i < bitmapSize; i++) {
        *(uint8_t*)(PageBitmap.Buffer + i) = 0;
    }
}