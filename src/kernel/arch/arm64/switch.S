.global switch_context
// void switch_context(Context* old, Context* newc)
switch_context:
    // 保存当前 sp 到 old->sp
    mov x2, sp
    str x2, [x0]          // old->sp = sp
    // 保存返回地址到 old->pc
    mov x2, x30
    str x2, [x0, #8]      // old->pc = x30

    // 恢复新上下文
    ldr x2, [x1]          // x2 = newc->sp
    mov sp, x2
    ldr x2, [x1, #8]      // x2 = newc->pc
    mov x30, x2
    ret 