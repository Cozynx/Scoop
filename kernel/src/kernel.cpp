#include <cstddef>
#include "BasicRenderer.h"
#include "cStr.h"

extern "C" void _start(Framebuffer* framebuffer, PSF1_FONT* psf1_font) {
    BasicRenderer newRenderer = BasicRenderer(framebuffer, psf1_font);
    newRenderer.Print(to_string((uint64_t)123456789));
    newRenderer.CursorPosition = {0, 16};
    newRenderer.Print(to_string((int64_t)-123456789));

    return;
}