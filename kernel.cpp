// kernel.cpp - your C++ starts here. This is the equivalent of Jack's Sys.init.
#include <stdint.h>   // allowed: comes from the compiler, just defines types
#include <stddef.h>

#include "screen/screen.h"
#include "memory/memory.h"
#include "architeture/architeture.h"


// ---- Entry point, called by boot.s ----
// extern "C" stops C++ from renaming ("mangling") the function,
// so the assembly can find it by the plain name "kernel_main".
extern "C" void kernel_main(uint32_t magic, word_t multiBootInfoAddr) {

    Memory::init(magic, multiBootInfoAddr);

    Screen::clear();
     Screen::setColor(10, 0);              // light green on black
    Screen::print(" XXXXX X   X X     XXXXX  XXXX        ***   **** \n");
    Screen::print("   X    X X  X     X      X   X      *   * *     \n");
    Screen::print("   X     X   X     XXXXX  XXXX       *   *  ***  \n");
    Screen::print("   X     X   X     X      X  X       *   *     * \n");
    Screen::print("   X     X   XXXXX XXXXX  X   X       ***  ****  \n");
    

    Screen::print("\n");
    Screen::print("\n");
    Screen::print("\n");

    Screen::setColor(10, 0);              // light green on black
    Screen::print("Hello from my kernel!\n");
    Screen::setColor(15, 0);
    Screen::print("Next up: Memory (kmalloc), String, Keyboard...\n");
    while (true) { }                      // never return
}