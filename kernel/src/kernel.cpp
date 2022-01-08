#include "kernelUtil.h"

extern "C" void _start(BootInfo* bootInfo) {
    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;      
    
    GlobalRenderer->CursorPosition = {0, GlobalRenderer->CursorPosition.Y + 16};
    GlobalRenderer->Print("Kernel Initialized Successfully");

    // asm("int $0x0e"); // Pretend a software interrupt
    GlobalRenderer->Clear(0x00ff0000);
    // int* test = (int*)0x80000000000;
    // *test = 2;

    while(true);
}