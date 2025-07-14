// arch/arm64/trap.cpp
// ARM64 中断/异常处理
#include "../../trap.hpp"
#include "../../panic.hpp"
#include "../../common.hpp"
#include "../../arch_interface.hpp"

extern "C" void vector_table();

namespace kernel {
namespace arch {

// ARM64 trap 初始化
void trap_init() {
    // 设置向量表
    uint64_t addr = (uint64_t)vector_table;
    asm volatile ("msr VBAR_EL1, %0" : : "r"(addr));
    // 使能 IRQ（清除 DAIF 的 I 位）
    asm volatile ("msr DAIFClr, #2");
    
    uint64_t vbar;
    asm volatile ("mrs %0, VBAR_EL1" : "=r"(vbar));
    printf("[arm64] trap_init: VBAR_EL1=0x%lx, vector_table=0x%lx\n", vbar, (uint64_t)vector_table);
    print("[arm64] trap_init: done\n");
}
} // namespace kernel 

extern "C" void arch_trap_entry(uint64_t pc, uint64_t sp, uint64_t cause, uint64_t value) {
    print("[arm64] arch_trap_entry\n");

    // 检查是否为 BCM2835 System Timer 1 中断
    // 直接读取 TIMER_CS 判断
    #define BCM2835_TIMER_BASE 0x3F003000UL
    #define TIMER_CS   (*(volatile uint32_t*)(BCM2835_TIMER_BASE + 0x00))
    if (TIMER_CS & (1 << 1)) {
        // 调用定时器中断处理函数
        kernel::driver::arm64::bcm2835_timer_interrupt_handler();
        // 构造 TrapContext 并分发为 TRAP_TIMER
        kernel::TrapContext ctx = {};
        ctx.pc = pc;
        ctx.sp = sp;
        ctx.cause = kernel::TRAP_TIMER;
        ctx.value = 0;
        kernel::trap_handler(ctx);
        return;
    }
    
}}