#include "../../include/PageFrameAllocator.h"

uint64_t freeMemory;
uint64_t reservedMemory;
uint64_t usedMemory;
bool Initialized = false;

PageFrameAllocator GlobalAllocator;

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
    // LockPages(PageBitmap.Buffer, PageBitmap.Size / 4096 + 1);
    ReservePages(0, memorySize / 4096 + 1);

    // reserve pages of unusable/reserved bitmap
    for(int i = 0; i < mMapEnteries; i++) {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((int64_t)mMap + (i * mMapDescSize));
        if(desc->type == 7) { // not UEFI conventional memory
            UnreservedPages(desc->physAddr, desc->numPages);
        }
    }
    ReservePages(0, 0x100); // Reserve between 0 and 0x100000
    LockPages(PageBitmap.Buffer, PageBitmap.Size / 4096 + 1);
}

void PageFrameAllocator::InitBitmap(size_t bitmapSize, void* bufferAddress) {
    PageBitmap.Size = bitmapSize;
    PageBitmap.Buffer = (uint8_t*)bufferAddress;
    for(int i = 0; i < bitmapSize; i++) {
        *(uint8_t*)(PageBitmap.Buffer + i) = 0;
    }
}

uint64_t pageBitmapIndex = 0;
void* PageFrameAllocator::RequestPage() {
    for(; pageBitmapIndex < PageBitmap.Size * 8; pageBitmapIndex++) {
        if(PageBitmap[pageBitmapIndex] == true) continue;
        LockPage((void*)(pageBitmapIndex * 4096));
        return (void*)(pageBitmapIndex * 4096);
    }
    return NULL; // TODO: Add PageFrameSwap(HDD driver + Swapping)
}

void PageFrameAllocator::FreePage(void* address) {
    uint64_t index = (uint64_t)address / 4096;
    if(PageBitmap[index] == false) return;
    if(PageBitmap.Set(index, false)) {
        freeMemory += 4096;
        usedMemory -= 4096;
        if(pageBitmapIndex > index) pageBitmapIndex = index;
    }
}

void PageFrameAllocator::LockPage(void* address) {
    uint64_t index = (uint64_t)address / 4096;
    if(PageBitmap[index] == true) return;
    if(PageBitmap.Set(index, true)) {
        freeMemory -= 4096;
        usedMemory += 4096;
    }
}

void PageFrameAllocator::UnreservedPage(void* address) {
    uint64_t index = (uint64_t)address / 4096;
    if(PageBitmap[index] == false) return;
    if(PageBitmap.Set(index, false)) {
        freeMemory += 4096;
        reservedMemory -= 4096;
        if(pageBitmapIndex > index) pageBitmapIndex = index;
    }
}

void PageFrameAllocator::ReservePage(void* address) {
    uint64_t index = (uint64_t)address / 4096;
    if(PageBitmap[index] == true) return;
    if(PageBitmap.Set(index, true)) {
        freeMemory -= 4096;
        reservedMemory += 4096;
    }
}

void PageFrameAllocator::FreePages(void* address, uint64_t pageCount) {
    for(int t = 0; t < pageCount; t++) {
        FreePage((void*)((uint64_t)address + (t * 4096)));
    }
}

void PageFrameAllocator::LockPages(void* address, uint64_t pageCount) {
    for(int t = 0; t < pageCount; t++) {
        LockPage((void*)((uint64_t)address + (t * 4096)));
    }
}

void PageFrameAllocator::UnreservedPages(void* address, uint64_t pageCount) {
    for(int t = 0; t < pageCount; t++) {
        UnreservedPage((void*)((uint64_t)address + (t * 4096)));
    }
}

void PageFrameAllocator::ReservePages(void* address, uint64_t pageCount) {
    for(int t = 0; t < pageCount; t++) {
        ReservePage((void*)((uint64_t)address + (t * 4096)));
    }
}

uint64_t PageFrameAllocator::GetFreeRAM() {
    return freeMemory;
}

uint64_t PageFrameAllocator::GetUsedRAM() {
    return usedMemory;
}

uint64_t PageFrameAllocator::GetReservedRAM() {
    return reservedMemory;
}
