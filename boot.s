# boot.s - the very first code that runs.
# The bootloader (QEMU or GRUB) finds the "multiboot header" below,
# loads the kernel into memory, and jumps to _start.

# ---- Multiboot header: a "magic stamp" saying "I am a kernel" ----
.set ALIGN,    1<<0              # align loaded modules on page boundaries
.set MEMINFO,  1<<1              # ask the bootloader for a memory map
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002        # the number bootloaders look for
.set CHECKSUM, -(MAGIC + FLAGS)  # MAGIC + FLAGS + CHECKSUM must equal 0

.section .multiboot, "a"
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# ---- A 16 KB stack. C++ can't run without one. ----
.section .bss, "aw", @nobits
.align 16
stack_bottom:
.skip 16384
stack_top:

# ---- Entry point ----
.section .text
.global _start
.type _start, @function

_start:
    mov $stack_top, %esp
    push %ebx
    push %eax
    call kernel_main

    # If kernel_main ever returns, stop the CPU forever.
    cli                          # disable interrupts
1:  hlt                          # halt
    jmp 1b                       # (in case something wakes it up)