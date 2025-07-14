#include "trap.hpp"
#include "common.hpp"
#include "printf.hpp"
#include "clock.hpp"
#include "arch_interface.hpp"

namespace kernel {

void trap_init() {
    printf("[trap] init...\n");
    arch::trap_init();
    printf("[trap] up.\n");
}

void trap_handler(TrapContext& ctx) {
    switch (ctx.cause) {
        case TRAP_TIMER:
            printf("[trap] Timer interrupt, ticks = %lu\n", clock_ticks());
            clock_interrupt();
            break;
        case TRAP_SYSCALL:
            printf("[trap] Syscall\n");
            // TODO: 调用系统调用处理函数
            break;
        case TRAP_EXTERNAL:
            printf("[trap] External interrupt\n");
            // TODO: 调用外部中断处理函数
            break;

        default:
            printf("[trap] Unknown trap: cause=%lu, pc=0x%lx\n", ctx.cause, ctx.pc);
            panic("Unknown trap");
            break;
    }
}

} // namespace kernel 