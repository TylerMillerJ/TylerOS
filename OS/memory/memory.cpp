// OS/memory/memory.cpp
#include "memory.h"
#include "boot/multiboot.h"
#include "math/math.h"
#include "panic/panic.h"

extern "C" char kernel_end[];          // set by the linker script

struct FreeBlock {
    word_t size;                       // size of this block in bytes
    FreeBlock* next;                   // next free block, or nullptr
};

static word_t heapStart = 0;
static word_t heapEnd = 0;
static FreeBlock* freeList = nullptr;

void Memory::init(uint32_t bootloaderMagic, word_t multibootInfoAddr) {
    if (bootloaderMagic != MULTIBOOT_MAGIC) {
        panic("Not started by a Multiboot bootloader");
    }

    auto* info = (MultibootInfo*)multibootInfoAddr;
    if ((info->flags & MULTIBOOT_FLAG_MMAP) == 0) {
        panic("Bootloader did not provide a memory map");
    }

    word_t kernelEnd = (word_t)kernel_end;

    // Find the usable region the kernel ends in; the heap is the rest of it
    word_t current = info->mmapAddr;
    word_t mapEnd  = info->mmapAddr + info->mmapLength;

    while (current < mapEnd) {
        auto* entry = (MemoryMapEntry*)current;
        uint64_t regionStart = entry->addr;
        uint64_t regionEnd   = entry->addr + entry->len;

        if (entry->type == MEMORY_USABLE &&
            regionStart <= kernelEnd && kernelEnd < regionEnd) {
            heapStart = Math::alignUp(kernelEnd, (word_t)4096);

            uint64_t maxAddress = (uint64_t)Math::maxOf<word_t>();
            heapEnd = (word_t)(regionEnd > maxAddress ? maxAddress : regionEnd);
        }

        current += entry->size + 4;    // +4 because "size" doesn't count itself
    }

    if (heapStart == 0 || heapStart >= heapEnd) {
        panic("No usable memory after the kernel");
    }

    // The whole heap starts as one big free block
    freeList = (FreeBlock*)heapStart;
    freeList->size = heapEnd - heapStart;
    freeList->next = nullptr;
}

word_t Memory::peek(word_t address) {
    return *(volatile word_t*)address;
}

void Memory::poke(word_t address, word_t value) {
    *(volatile word_t*)address = value;
}

void* Memory::alloc(word_t size) {
    // TODO: walk freeList, find a block big enough, split it, return its address
    return nullptr;
}

void Memory::deAlloc(void* object) {
    // TODO: put the block back on freeList and merge with free neighbors
}