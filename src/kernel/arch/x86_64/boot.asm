; x86-64 启动汇编，Multiboot2 规范
; 入口符号为 _boot，由QEMU/GRUB加载

section .multiboot
    align 8
multiboot_header:
    dd 0xE85250D6              ; Multiboot2 magic
    dd 0                       ; architecture (0 = i386)
    dd multiboot_header_end - multiboot_header ; header length
    dd 0x100000000 - (0xE85250D6 + 0 + (multiboot_header_end - multiboot_header)) ; checksum

    ; end tag
    dw 0                        ; type = 0
    dw 0                        ; reserved
    dd 8                        ; size = 8
multiboot_header_end:

section .text
    global _boot
    extern stack_top

_boot:
    lea rax, [rel stack_top]
    mov rsp, rax
    extern arch_entry
    call arch_entry

.hang:
    hlt
    jmp .hang

[section .note.GNU-stack noalloc noexec nowrite progbits] 