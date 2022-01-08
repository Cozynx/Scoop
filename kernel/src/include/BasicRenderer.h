#pragma once
#include "math.h"
#include "FrameBuffer.h"
#include "SimpleFonts.h"
#include <stdint.h>

class BasicRenderer{
public:
    BasicRenderer(Framebuffer* targetFrameBuffer, PSF1_FONT* psf1_font);
    Point CursorPosition;
    Framebuffer* TargetFrameBuffer;
    PSF1_FONT* PSF1_font;
    unsigned int Color;
    unsigned int ClearColor;
    void Print(const char* str);
    void putChar(char chr, unsigned int xOff, unsigned int yOff);
    void putChar(char chr);
    void Clear();
    void Next();
    void ClearChar();
};

extern BasicRenderer* GlobalRenderer;