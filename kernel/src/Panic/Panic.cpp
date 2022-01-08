#include "panic.h"
#include "../include/BasicRenderer.h"

void Panic(const char* panicMessage) {
    GlobalRenderer->Clear(0x00adefff);

    GlobalRenderer->CursorPosition = {0, 0};
    GlobalRenderer->Color = 0x52a965ff;

    GlobalRenderer->Print("Kernel Panic");
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Print(panicMessage);
}