// panic.cpp
#include "panic.h"
#include "screen/screen.h"

void panic(const char* message) {
    Screen::setColor(15, 4);           // white on red, so it stands out
    Screen::print("\nKERNEL PANIC: ");
    Screen::print(message);
    Screen::print("\n");

    asm volatile ("cli");              // turn off interrupts so nothing wakes the CPU
    while (true) {
        asm volatile ("hlt");          // halt until the next interrupt (which can't come)
    }
}