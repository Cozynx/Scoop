#include "Interrupts.h"
#include "../Panic/Panic.h"

__attribute__((interrupt)) void PageFault_Handler(struct Interrupt_frame* frame) {
    Panic("Page Fault Detected");

    while(true);
}