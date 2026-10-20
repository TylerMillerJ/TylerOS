#include <stdint.h>   // allowed: comes from the compiler, just defines types
#include <stddef.h>

#include "screen.h"


// ---- A tiny "Screen" class (like Jack's Output) ----
// On x86, the text screen is 80x25 characters living at memory address 0xB8000.
// Each character is 2 bytes: the letter, then a color byte.
// This is the same idea as Jack's screen memory map at 16384.
    void Screen::clear() {
        for (size_t i = 0; i < WIDTH * HEIGHT; i++)
            buffer[i] = entry(' ', color);
        row = col = 0;
    }

    void Screen::putChar(char c) {
        if (c == '\n') { newline(); return; }
        buffer[row * WIDTH + col] = entry(c, color);
        if (++col == WIDTH) newline();
    }

    void Screen::print(const char* s) {
        for (size_t i = 0; s[i] != '\0'; i++)
            putChar(s[i]);
    }

    void Screen::setColor(uint8_t fg, uint8_t bg) { color = fg | (bg << 4); }

    uint16_t Screen::entry(char c, uint8_t colorByte) {
        return (uint16_t)(uint8_t)c | ((uint16_t)colorByte << 8);
    }
    void Screen::newline() {
        col = 0;
        if (++row == HEIGHT) row = 0;     // no scrolling yet - your first exercise!
    }

    void Screen::printHex(uint32_t value) {
    const char* digits = "0123456789ABCDEF";
    print("0x");
    for (int shift = 28; shift >= 0; shift -= 4) {
        putChar(digits[(value >> shift) & 0xF]);   // one hex digit = 4 bits
    }
}
