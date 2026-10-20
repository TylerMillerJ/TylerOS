/* linker.ld - tells the linker how to lay the kernel out in memory. */

ENTRY(_start)

SECTIONS
{
    . = 1M;

    .text : ALIGN(4K)
    {
        KEEP(*(.multiboot))
        *(.text*)
    }

    .rodata : ALIGN(4K) { *(.rodata*) }
    .data   : ALIGN(4K) { *(.data*) }
    .bss    : ALIGN(4K) { *(COMMON) *(.bss*) }

    kernel_end = .;           /* first address after the whole kernel, including the stack */
}