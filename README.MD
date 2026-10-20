# TylerOS

A small operating system kernel for 32-bit x86, written from scratch in freestanding C++ and x86 assembly. It boots in QEMU through the Multiboot protocol and runs directly on the (emulated) hardware, with no standard library or host OS underneath it.

This is a Personal Project project to understand how operating systems works from the first instruction after boot upward.

**Status:** in progress. The kernel boots, prints to the screen, and has an integer math library. Memory management is being implemented now.

---

## Build and Run

### Requirements

- **Clang** (C++20) and **LLD**: compiles and links for bare-metal x86 with `--target=i686-elf`, so no custom cross-compiler is needed
- **Make**
- **QEMU** (`qemu-system-i386`): emulates the PC the kernel runs on

On Fedora:

```bash
sudo dnf install clang lld make qemu-system-x86
```

On Ubuntu/Debian:

```bash
sudo apt install clang lld make qemu-system-x86
```

### Commands

```bash
make          # build mykernel.bin
make run      # build if needed, then boot it in QEMU
make clean    # remove build output
```

The Makefile automatically finds every `.cpp` and `.s` file under `OS/`, so new files are picked up without editing it.

---

## Project Layout

```
TylerOS/
├── boot.s            # entry point: Multiboot header, stack setup, call into C++
├── kernel.cpp        # kernel_main(): initializes each library in order
├── linker.ld         # memory layout: kernel loaded at 1 MB, sections, kernel_end
├── Makefile
└── OS/
    ├── architeture/  # word size and word_t type
    ├── boot/         # Multiboot structures
    ├── math/         # integer math library
    ├── memory/       # peek/poke and heap (in progress)
    ├── panic/        # fatal error handler
    └── screen/       # VGA text-mode driver
```

---

## Libraries

| Library | Files | Status | Description |
|---|---|---|---|
| Screen | `OS/screen/` | Working | VGA text-mode driver: writes characters and colors to video memory at `0xB8000`; `print`, `putChar`, `printHex`, `setColor`, `clear`, `printBig` (large text from a bitmap font) |
| Math | `OS/math/` | Working | Templated integer math restricted to integer types with a C++20 concept: `abs`, `min`, `max`, `multiply` (shift-and-add), `divide` (shift-and-subtract), `sqrt` (bitwise), `gcd`, `lcm`, `alignUp`, `minOf`/`maxOf` |
| Panic | `OS/panic/` | Working | `panic(message)`: prints an error in red, disables interrupts, and halts the CPU |
| Architecture | `OS/architeture/` | Working | `WORD_BITS` and `word_t`, derived from the compiler's pointer size, so the code adapts if the target changes to 64-bit |
| Multiboot | `OS/boot/` | Working | Structures for the info and memory map the bootloader passes to the kernel |
| Memory | `OS/memory/` | In progress | `peek`/`poke` for raw memory access; heap setup from the bootloader's memory map; `alloc`/`deAlloc` free-list allocator |

<!-- Add new libraries as rows above -->

---

## Internals

### Boot sequence

1. QEMU's built-in Multiboot loader finds the header in `boot.s` (magic number `0x1BADB002`) and loads the kernel at 1 MB.
2. `_start` in `boot.s` sets up a 16 KB stack, pushes the bootloader's magic value (`eax`) and info pointer (`ebx`), and calls `kernel_main`.
3. `kernel_main` initializes each library and runs the kernel.

### Memory layout

| Address | Contents |
|---|---|
| `0x00000`–`0xFFFFF` | Reserved for BIOS data, video memory (`0xB8000`), and ROM |
| `0x100000` (1 MB) | Kernel code, data, and stack, placed by `linker.ld` |
| `kernel_end` onward | Heap, aligned to 4 KB, sized from the bootloader's memory map |

### Design notes

- **Freestanding:** no standard library is available, so everything above the hardware is written by hand. Only compiler-provided headers like `<stdint.h>` and `<stddef.h>` are used.
- **Integer-only kernel:** compiled with `-mno-sse -mno-mmx` because the floating-point unit is not enabled yet.
- **Compile-time safety:** templates are restricted to integer types, and `peek`/`poke` reject any address type other than `word_t` at compile time.

---

## Roadmap

- [ ] Finish the heap allocator: `alloc`, `deAlloc`, and coalescing of adjacent free blocks
- [ ] `kprintf` with `%d`, `%x`, `%s`, `%c`
- [ ] Screen scrolling
- [ ] Benchmark software `multiply`/`divide` against hardware `imul`/`div` using `rdtsc`
- [ ] GDT and IDT, with CPU exception handlers
- [ ] Hardware interrupts (PIC) and a timer (PIT)
- [ ] Keyboard driver and a simple shell
- [ ] Paging and a physical page allocator
- [ ] Multitasking and a scheduler