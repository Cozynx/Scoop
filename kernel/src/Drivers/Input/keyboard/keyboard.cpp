#include "../../../include/keyboard.h"

bool isCapital;

void HandleKeyboard(uint8_t scancode) {
    switch(scancode) {
    case LeftShift:
        isCapital = true;
        return;
    case LeftShift + 0x80:
        isCapital = false;
        return;
    case RightShift:
        isCapital = true;
        return;
    case RightShift + 0x80:
        isCapital = false;
        return;
    case Enter:
        GlobalRenderer->Next();
        return;
    case SpaceBar:
        GlobalRenderer->putChar(' ');
        return;
    case BackSpace:
        GlobalRenderer->ClearChar();
        return;
    case CapsLock:
        isCapital = true;
        return;
    case CapsLock + 0x80:
        isCapital = false;
        return;
    }

    char ascii = QWERTYKeyboard::Translate(scancode, isCapital);

    if(ascii != 0) GlobalRenderer->putChar(ascii);
}