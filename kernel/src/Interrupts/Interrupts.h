#pragma once
#include "../include/BasicRenderer.h"
#include "../include/IO.h"
#include "../include/keyboard.h"
#include "../Panic/Panic.h"
#include "../include/mouse.h"
#include "../Scheduling/PIT/pit.h"

#define PIC1_COMMAND 0x20   // master PIC commandline
#define PIC1_DATA 0x21      // Data Line for Master PIC
#define PIC2_COMMAND 0xA0   // Slave PIC commandline
#define PIC2_DATA 0xA1      // Data Line for Slave PIC
#define PIC_EOI 0x20        // End of interrupt

#define ICW1_INIT 0x10
#define ICW1_ICW4 0X01
#define ICW4_8086 0x01

struct interrupt_Frame;
__attribute__((interrupt)) void PageFault_Handler(interrupt_Frame* frame);
__attribute__((interrupt)) void DoubleFault_Handler(interrupt_Frame* frame);
__attribute__((interrupt)) void GPFault_Handler(interrupt_Frame* frame);
__attribute__((interrupt)) void KeyboardInt_Handler(interrupt_Frame* frame);
__attribute__((interrupt)) void MouseInt_Handler(interrupt_Frame* frame);
__attribute__((interrupt)) void PITInt_Handler(interrupt_Frame* frame);

void RemapPIC();
void PIC_EndMaster();
void PIC_EndSlave();