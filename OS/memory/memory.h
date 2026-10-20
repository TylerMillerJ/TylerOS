// OS/memory/memory.h
#pragma once
#include <stdint.h>
#include "architeture/architeture.h"

class Memory {
public:
    Memory() = delete;

    /** Set up the heap using the memory map from the bootloader */
    static void init(uint32_t bootloaderMagic, word_t multibootInfoAddr);

    /** Return the word stored at the given address */
    static word_t peek(word_t address);

    /** Store a word at the given address */
    static void poke(word_t address, word_t value);

    // Reject any address type other than word_t at compile time
    template <typename T> static word_t peek(T address) = delete;
    template <typename T> static void poke(T address, word_t value) = delete;

    /** Allocate a block of at least `size` bytes; returns its address */
    static void* alloc(word_t size);

    /** Return a block from alloc to the heap */
    static void deAlloc(void* object);
};