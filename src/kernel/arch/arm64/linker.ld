/* arch/arm64/linker.ld
 * ARM64 内核链接脚本，指定加载地址和段布局
 */

ENTRY(_boot)
SECTIONS
{
    . = 0x80000 ;
    . = ALIGN(4K);
    .text : {
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