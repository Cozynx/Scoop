#include <cstdint>
#include "includes/BasicRenderer.h"
#include "includes/cStr.h"
#include "includes/efiMemory.h"
#include "includes/memory.h"
#include "includes/Bitmap.h"
#include "includes/PageFrameAllocator.h"

struct BootInfo{
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
};

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

extern "C" void _start(BootInfo* bootInfo) {
    BasicRenderer newRenderer = BasicRenderer(bootInfo->framebuffer, bootInfo->psf1_Font);

    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    PageFrameAllocator newAllocator;
    newAllocator.ReadEfiMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    // Reserve Kernel Size
    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;

    newAllocator.LockPages(&_KernelStart, kernelPages);

    newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
    newRenderer.Print("Free RAM: ");
    newRenderer.Print(to_string(newAllocator.GetFreeRAM() / 1024));
    newRenderer.Print(" KB");

    newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
    newRenderer.Print("Used RAM: ");
    newRenderer.Print(to_string(newAllocator.GetUsedRAM() / 1024));
    newRenderer.Print(" KB");

    newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
    newRenderer.Print("Reserved RAM: ");
    newRenderer.Print(to_string(newAllocator.GetReservedRAM() / 1024));
    newRenderer.Print(" KB");

    for(int t = 0; t < 20; t++) {
        void* address = newAllocator.RequestPage();
        newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
        newRenderer.Print(to_hstring((uint64_t)address));        
    }

    return;
}