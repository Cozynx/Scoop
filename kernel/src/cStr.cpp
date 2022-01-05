#include "includes/cStr.h"

char uintToStringOutput[128];
const char* to_string(uint64_t value) {
    uint8_t size;
    uint64_t sizeTest = value;
    while(sizeTest / 10 > 0) {
        sizeTest /= 10;
        size++;
    }

    uint8_t index = 0;
    while(value / 10 > 0) {
        uint8_t remainder = value % 10;
        value /= 10;
        uintToStringOutput[size - index] = remainder + '0';
        index++;
    }
    uint8_t remainder = value % 10;
    uintToStringOutput[size - index] = remainder + '0';
    uintToStringOutput[size + 1] = 0;
    return uintToStringOutput;
}

char HexToStringOutput[128];
const char* to_hstring(uint64_t value) {
    uint64_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 8 * 2 - 1;
    for(uint8_t i = 0; i < size; i++) {
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        HexToStringOutput[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        HexToStringOutput[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    HexToStringOutput[size + 1] = 0;
    return HexToStringOutput;
}

char HexToStringOutput32[128];
const char* to_hstring(uint32_t value) {
    uint32_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 4 * 2 - 1;
    for(uint8_t i = 0; i < size; i++) {
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        HexToStringOutput32[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        HexToStringOutput32[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    HexToStringOutput32[size + 1] = 0;
    return HexToStringOutput32;
}

char HexToStringOutput16[128];
const char* to_hstring(uint16_t value) {
    uint16_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 2 * 2 - 1;
    for(uint8_t i = 0; i < size; i++) {
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        HexToStringOutput16[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        HexToStringOutput16[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    HexToStringOutput16[size + 1] = 0;
    return HexToStringOutput16;
}

char HexToStringOutput8[128];
const char* to_hstring(uint8_t value) {
    uint8_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 1 * 2 - 1;
    for(uint8_t i = 0; i < size; i++) {
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        HexToStringOutput8[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        HexToStringOutput8[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    HexToStringOutput8[size + 1] = 0;
    return HexToStringOutput8;
}

char intToStringOutput[128];
const char* to_string(int64_t value) {
    uint8_t isNegative = 0;

    if(value < 0){
        isNegative = 1;
        value *= -1;
    }

    uint8_t size;
    uint64_t sizeTest = value;
    while(sizeTest / 10 > 0) {
        sizeTest /= 10;
        size++;
        intToStringOutput[0] = '-';
    }

    uint8_t index = 0;
    while(value / 10 > 0) {
        uint8_t remainder = value % 10;
        value /= 10;
        intToStringOutput[isNegative + size - index] = remainder + '0';
        index++;
    }
    uint8_t remainder = value % 10;
    intToStringOutput[isNegative + size - index] = remainder + '0';
    intToStringOutput[isNegative + size + 1] = 0;
    return intToStringOutput;
}

char doubleToStringOutput[128];
const char* to_string(double value, uint8_t decimal_places) {
    if(decimal_places > 20) decimal_places = 20;

    char* intPtr = (char*)to_string((int64_t)value);
    char* doublePtr = doubleToStringOutput;

    if(value < 0) {
        value *= -1;
    }

    while(*intPtr != 0) {
        *doublePtr = *intPtr;
        intPtr++;
        doublePtr++;
    }

    *doublePtr = '.';
    doublePtr++;

    double newValue = value - (int)value;

    for(uint8_t i = 0; i < decimal_places; i++) {
        newValue *= 10;
        *doublePtr = (int)newValue + '0';
        newValue -= (int)newValue;
        doublePtr++;
    }

    *doublePtr = 0;
    return doubleToStringOutput;
}

const char* to_string(double value) {
    return to_string(value, 2);
}