#pragma once

#include <stdint.h>   // allowed: comes from the compiler, just defines types
#include <stddef.h>

// ---- A tiny "Screen" class (like Jack's Output) ----
// On x86, the text screen is 80x25 characters living at memory address 0xB8000.
// Each character is 2 bytes: the letter, then a color byte.
// This is the same idea as Jack's screen memory map at 16384.

class Screen {
public:
    static void clear();

    static void putChar(char c);

    static void print(const char* s);

    static void setColor(uint8_t fg, uint8_t bg);
    
    static void printHex(uint32_t value);

private:
    static constexpr size_t WIDTH = 80, HEIGHT = 25;
    static inline volatile uint16_t* const buffer = (volatile uint16_t*)0xB8000;
    static inline size_t row = 0, col = 0;
    static inline uint8_t color = 0x0F;   // white on black

    static uint16_t entry(char c, uint8_t colorByte);

    static void newline();
};
