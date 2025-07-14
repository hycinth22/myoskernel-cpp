.global switch_context
switch_context:
    movq %rsp, (%rdi)        # old->rsp = rsp
    movq 8(%rdi), %rax       # rax = old->rip
    movq %rax, 8(%rdi)
    movq (%rsi), %rsp        # rsp = new->rsp
    movq 8(%rsi), %rax       # rax = new->rip
    jmp *%rax 
.section .note.GNU-stack,"",@progbits 