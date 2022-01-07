#pragma once

#include <cstdint>
#include "include/BasicRenderer.h"
#include "include/cStr.h"
#include "include/efiMemory.h"
#include "include/memory.h"
#include "include/Bitmap.h"
#include "include/PageFrameAllocator.h"
#include "include/PageMapIndexer.h"
#include "include/Paging.h"
#include "include/PageTableManager.h"
#include "GDT/gdt.h"
#include "Interrupts/IDT.h"

struct BootInfo{
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
};

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

struct KernelInfo {
    PageTableManager* pageTableManager;
};

KernelInfo InitializeKernel(BootInfo* bootInfo);