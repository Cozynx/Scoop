#include "../../include/BasicRenderer.h"

BasicRenderer* GlobalRenderer;

BasicRenderer::BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_font) {
	TargetFrameBuffer = targetFramebuffer;
	PSF1_font = psf1_font;
	Color = 0xffffffff;
	CursorPosition = {0,0};
}

void BasicRenderer::Print(const char* str) {
	char* chr = (char*)str;
	while(*chr != 0) {
		putChar(*chr, CursorPosition.X, CursorPosition.Y);
		CursorPosition.X+=8;
		if(CursorPosition.X + 8 > TargetFrameBuffer->Width) {
			CursorPosition.X = 0;
			CursorPosition.Y += 16;
		}
		chr++;
	}
}

void BasicRenderer::putChar(char chr, unsigned int xOff, unsigned int yOff) {
    unsigned int* pixPtr = (unsigned int*)TargetFrameBuffer->BaseAddress;
    char* fontPtr = (char*)PSF1_font->glyphBuffer + (chr * PSF1_font->psf1_Header->charsize);
    for(unsigned long y = yOff; y < yOff + 16; y++) {
        for(unsigned long x = xOff; x < xOff + 8; x++) {
            if((*fontPtr & (0b10000000 >> (x - xOff))) > 0) {
                *(unsigned int*)(pixPtr + x + (y * TargetFrameBuffer->PixelsPerScanline)) = Color;
            }
        }
		fontPtr++;
    }
}

void BasicRenderer::Clear(uint32_t color) {
	uint64_t fbBase = (uint64_t)TargetFrameBuffer->BaseAddress;
	uint64_t bytesPerScanLine = TargetFrameBuffer->PixelsPerScanline * 4;
	uint64_t fbHeight = TargetFrameBuffer->Height;
	uint64_t fbSize = TargetFrameBuffer->BufferSize;

	for(int verticalScanLine = 0; verticalScanLine < fbHeight; verticalScanLine++) {
		uint64_t pixPtrBase = fbBase + (bytesPerScanLine * verticalScanLine);
		for(uint32_t* pixPtr = (uint32_t*)pixPtrBase; pixPtr < (uint32_t*)(pixPtrBase + bytesPerScanLine); pixPtr++) {
			*pixPtr = color;
		}
	}
}

void BasicRenderer::Next() {
	CursorPosition.X = 0;
	CursorPosition.Y += 16;
}