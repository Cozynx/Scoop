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
    uint32_t MouseCursorBuffer[16 * 16];
    uint32_t MouseCursorBufferAfter[16 * 16];
    unsigned int Color;
    unsigned int ClearColor;
    void Print(const char* str);
    void putChar(char chr, unsigned int xOff, unsigned int yOff);
    void putChar(char chr);
    void PutPix(uint32_t x, uint32_t y, uint32_t color);
    void Clear();
    void Next();
    void ClearChar();
    void DrawOverlayMouseCursor(uint8_t* mouseCursor, Point position, uint32_t color);
    void ClearMouseCursor(uint8_t* mouseCursor, Point position);
    bool MouseDrawn;
    uint32_t GetPix(uint32_t x, uint32_t y);
};

extern BasicRenderer* GlobalRenderer;