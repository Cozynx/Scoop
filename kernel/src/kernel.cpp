#include "kernelUtil.h"

extern "C" void _start(BootInfo* bootInfo) {
    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;      
    BasicRenderer Renderer = BasicRenderer(bootInfo->framebuffer, bootInfo->psf1_Font);

    Renderer.CursorPosition = {0, Renderer.CursorPosition.Y + 16};
    Renderer.Print("Kernel Initialized Successfully");

    while(true);
}