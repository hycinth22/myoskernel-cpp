.global isr_timer
isr_timer:
    pushq $0
    call timer_handler
    addq $8, %rsp
    iretq

.global isr_default
isr_default:
    pushq $0
    call default_handler
    addq $8, %rsp
    iretq

.global idt_load
idt_load:
    lidt (%rdi)
    ret 

.section .note.GNU-stack,"",@progbits 