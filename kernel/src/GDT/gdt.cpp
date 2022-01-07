#include "gdt.h"

__attribute__((aligned(0x1000)))
GDT DefaultGDT = {
    {0, 0, 0, 0x00, 0x00, 0}, // Null segment
    {0, 0, 0, 0x9a, 0xa0, 0}, // Kernel Code segment
    {0, 0, 0, 0x92, 0xa0, 0}, // Kernel Data segment
    {0, 0, 0, 0x00, 0x00, 0}, // User null segment
    {0, 0, 0, 0x9a, 0xa0, 0}, // User Code segment
    {0, 0, 0, 0x92, 0xa0, 0}, // User Data segment
};