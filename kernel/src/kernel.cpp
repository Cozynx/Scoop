#include <cstdint>
#include "BasicRenderer.h"
#include "cStr.h"

extern "C" void _start(Framebuffer* framebuffer, PSF1_FONT* psf1_font) {
    BasicRenderer newRenderer = BasicRenderer(framebuffer, psf1_font);
    newRenderer.Print(to_string((uint64_t)123456789));
    newRenderer.CursorPosition = {0, 16};
    newRenderer.Print(to_string((int64_t)-123456789));
    newRenderer.CursorPosition = {0, 32};
    newRenderer.Print(to_string((double)1.323, 3));
    newRenderer.CursorPosition = {0, 48};
    newRenderer.Print(to_hstring((uint64_t)0xF0));
    newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
    newRenderer.Print(to_hstring((uint32_t)0xF0));
    newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
    newRenderer.Print(to_hstring((uint16_t)0xF0));
    newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
    newRenderer.Print(to_hstring((uint8_t)0xF0));
    
    return;
}