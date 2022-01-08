#include "panic.h"
#include "../include/BasicRenderer.h"

void Panic(const char* panicMessage) {
    GlobalRenderer->ClearColor = 0x00adefe3;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {0, 0};
    GlobalRenderer->Color = 0x52a965ff;

    GlobalRenderer->Print("Kernel Panic");
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Print(panicMessage);
}