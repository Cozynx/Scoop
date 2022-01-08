#include "Interrupts.h"

__attribute__((interrupt)) void PageFault_Handler(struct Interrupt_frame* frame) {
    GlobalRenderer->Print("Page Fault Detected!");

    while(true);
}