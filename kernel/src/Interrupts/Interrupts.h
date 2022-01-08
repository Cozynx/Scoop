#pragma once
#include "../include/BasicRenderer.h"

struct Interrupt_Frame;
__attribute__((interrupt)) void PageFault_Handler(struct Interrupt_frame* frame);