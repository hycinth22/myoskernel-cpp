// ARM64 启动汇编
// 入口符号为 _boot，由QEMU/固件加载
    .section .text
    .global _boot
    .align 7

_boot:
    mrs x1, mpidr_el1
    and x1, x1, #0xff

    // 只允许第一个CPU执行，其它CPU直接进入低功耗等待
    cbnz x1, _loop

_entry:
    msr DAIFSet, #0xf
    ldr x0, =_stack_top
    mov sp, x0
    bl arch_entry

// 死循环防止返回
_loop:  wfe
    b _loop

.section .bss
.align 12
_stack:
    .skip 0x4000      // 16KB 栈空间
_stack_top: 