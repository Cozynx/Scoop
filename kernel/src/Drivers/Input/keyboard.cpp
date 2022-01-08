#include "../../include/keyboard.h"

bool isLeftShiftPressed;
bool isRightShiftPressed;

void HandleKeyboard(uint8_t scancode) {
    switch(scancode) {
    case LeftShift:
        isLeftShiftPressed = true;
        return;
    case LeftShift + 0x80:
        isLeftShiftPressed = false;
        return;
    case RightShift:
        isRightShiftPressed = true;
        return;
    case RightShift + 0x80:
        isRightShiftPressed = false;
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
        isLeftShiftPressed = true;
        return;
    case CapsLock + 0x80:
        isLeftShiftPressed = false;
        return;
    }

    char ascii = QWERTYKeyboard::Translate(scancode, isLeftShiftPressed || isRightShiftPressed);

    if(ascii != 0) GlobalRenderer->putChar(ascii);
}