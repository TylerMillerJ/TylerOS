// multiboot.h - structures the Multiboot bootloader hands to the kernel
#pragma once
#include <stdint.h>

constexpr uint32_t MULTIBOOT_MAGIC     = 0x2BADB002;   // bootloader's signature in eax
constexpr uint32_t MULTIBOOT_FLAG_MMAP = 1 << 6;       // "memory map is valid"
constexpr uint32_t MEMORY_USABLE       = 1;            // memory map type for usable RAM

struct MultibootInfo {
    uint32_t flags;
    uint32_t memLower, memUpper;
    uint32_t bootDevice, cmdline, modsCount, modsAddr;
    uint32_t syms[4];
    uint32_t mmapLength, mmapAddr;
} __attribute__((packed));

struct MemoryMapEntry {
    uint32_t size;      // size of this entry, not counting this field
    uint64_t addr;      // start of the region
    uint64_t len;       // length of the region
    uint32_t type;      // 1 = usable, anything else = reserved
} __attribute__((packed));