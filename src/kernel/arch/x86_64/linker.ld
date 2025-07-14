/* arch/x86_64/linker.ld
 * x86-64 内核链接脚本，指定加载地址和段布局
 */

ENTRY(_boot)
SECTIONS
{
    . = 1M; /* 内核加载到1MB */
    . = ALIGN(4K);
    .text : {
        *(.multiboot*)
        *(.text*)
    } :text

    . = ALIGN(4K);
    .rodata : {
        *(.rodata*)
    } :rodata

    . = ALIGN(4K);
    .data : {
        *(.data*)
    } :data

    . = ALIGN(4K);
    .bss : {
        *(COMMON)
        *(.bss*)
        stack_bottom = .;
        . = . + 16384;
        stack_top = .;
    } :data
}

 PHDRS
  {
    text PT_LOAD FLAGS(5); /* R_X */
    data PT_LOAD FLAGS(6); /* R_W */
    rodata PT_LOAD FLAGS(4); /* R__ */
  }