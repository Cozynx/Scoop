#pragma once
#include "math.h"
#include "FrameBuffer.h"
#include "SimpleFonts.h"

class BasicRenderer{
public:
    BasicRenderer(Framebuffer* targetFrameBuffer, PSF1_FONT* psf1_font);
    Point CursorPosition;
    Framebuffer* TargetFrameBuffer;
    PSF1_FONT* PSF1_font;
    unsigned int Color;
    void Print(const char* str);
    void putChar(char chr, unsigned int xOff, unsigned int yOff);
};

extern BasicRenderer* GlobalRenderer;