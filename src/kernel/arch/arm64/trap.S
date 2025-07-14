.section .text
.align 11
.global vector_table
vector_table:
    b sync_el1t_handler      // 0
    b irq_el1t_handler       // 1
    b fiq_el1t_handler       // 2
    b serr_el1t_handler      // 3
    b sync_el1h_handler      // 4
    b irq_el1h_handler       // 5
    b fiq_el1h_handler       // 6
    b serr_el1h_handler      // 7
    b sync_el0_64_handler    // 8
    b irq_el0_64_handler     // 9
    b fiq_el0_64_handler     // 10
    b serr_el0_64_handler    // 11
    b sync_el0_32_handler    // 12
    b irq_el0_32_handler     // 13
    b fiq_el0_32_handler     // 14
    b serr_el0_32_handler    // 15

.global sync_el1t_handler
sync_el1t_handler:
    mrs x0, elr_el1
    mov x1, sp
    mrs x2, esr_el1
    mov x3, #0
    bl arch_trap_entry
    eret
.global irq_el1t_handler
irq_el1t_handler:
    mrs x0, elr_el1
    mov x1, sp
    mrs x2, esr_el1
    mov x3, #1
    bl arch_trap_entry
    eret
.global fiq_el1t_handler
fiq_el1t_handler:
    mrs x0, elr_el1
    mov x1, sp
    mrs x2, esr_el1
    mov x3, #2
    bl arch_trap_entry
    eret
.global serr_el1t_handler
serr_el1t_handler:
    mrs x0, elr_el1
    mov x1, sp
    mrs x2, esr_el1
    mov x3, #3
    bl arch_trap_entry
    eret
.global sync_el1h_handler
sync_el1h_handler:
    mrs x0, elr_el1
    mov x1, sp
    mrs x2, esr_el1
    mov x3, #4
    bl arch_trap_entry
    eret
.global irq_el1h_handler
irq_el1h_handler:
    mrs x0, elr_el1
    mov x1, sp
    mrs x2, esr_el1
    mov x3, #5
    bl arch_trap_entry
    eret
.global fiq_el1h_handler
fiq_el1h_handler:
    mrs x0, elr_el1
    mov x1, sp
    mrs x2, esr_el1
    mov x3, #6
    bl arch_trap_entry
    eret
.global serr_el1h_handler
serr_el1h_handler:
    mrs x0, elr_el1
    mov x1, sp
    mrs x2, esr_el1
    mov x3, #7
    bl arch_trap_entry
    eret
.global sync_el0_64_handler
sync_el0_64_handler:
    mrs x0, elr_el1
    mov x1, sp
    mrs x2, esr_el1
    mov x3, #8
    bl arch_trap_entry
    eret
.global irq_el0_64_handler
irq_el0_64_handler:
    mrs x0, elr_el1
    mov x1, sp
    mrs x2, esr_el1
    mov x3, #9
    bl arch_trap_entry
    eret
.global fiq_el0_64_handler
fiq_el0_64_handler:
    mrs x0, elr_el1
    mov x1, sp
    mrs x2, esr_el1
    mov x3, #10
    bl arch_trap_entry
    eret
.global serr_el0_64_handler
serr_el0_64_handler:
    mrs x0, elr_el1
    mov x1, sp
    mrs x2, esr_el1
    mov x3, #11
    bl arch_trap_entry
    eret
.global sync_el0_32_handler
sync_el0_32_handler:
    mrs x0, elr_el1
    mov x1, sp
    mrs x2, esr_el1
    mov x3, #12
    bl arch_trap_entry
    eret
.global irq_el0_32_handler
irq_el0_32_handler:
    mrs x0, elr_el1
    mov x1, sp
    mrs x2, esr_el1
    mov x3, #13
    bl arch_trap_entry
    eret
.global fiq_el0_32_handler
fiq_el0_32_handler:
    mrs x0, elr_el1
    mov x1, sp
    mrs x2, esr_el1
    mov x3, #14
    bl arch_trap_entry
    eret
.global serr_el0_32_handler
serr_el0_32_handler:
    mrs x0, elr_el1
    mov x1, sp
    mrs x2, esr_el1
    mov x3, #15
    bl arch_trap_entry
    eret 