// ARMv8 通用定时器（仅适用于支持 ARM Generic Timer 的平台，如 QEMU virt）
#include "../../common.hpp"

namespace kernel {
    namespace driver {
    namespace arm64 {

    #if defined(__aarch64__)

    void generic_timer_init() {
        printf("[arm64] generic_timer_init\n");
        uint32_t freq;
        // 获得定时器时钟频率
        asm volatile("mrs %0, cntfrq_el0" : "=r"(freq));
        uint32_t interval = freq / 100; // 单位为 Hz
        printf("[arm64] clock freq %d interval %d \n", freq, interval);
        // 设置下一个定时器中断间隔
        asm volatile("msr cntp_tval_el0, %0" : : "r"(interval));
        // 使能物理定时器中断
        asm volatile("msr cntp_ctl_el0, %0" : : "r"(1));
        // 清除中断屏蔽（开中断）
        asm volatile("msr DAIFClr, #2");
    }
    
    void generic_timer_interrupt_handler() {
        kernel::print("[arm64] 时钟中断，调度...\n");
        kernel::yield();

        // 设置下一个定时器中断
        uint32_t freq;
        asm volatile("mrs %0, cntfrq_el0" : "=r"(freq));
        uint32_t interval = freq / 100;
        asm volatile("msr cntp_tval_el0, %0" : : "r"(interval));
    }
    #endif 
}}}