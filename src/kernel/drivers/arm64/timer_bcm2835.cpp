// bcm2835_timer.cpp
// BCM2835 System Timer 驱动，适用于树莓派3B（raspi3b）
#include "../../common.hpp"
#include "../../param.hpp"

// BCM2835 System Timer 寄存器基地址
#define BCM2835_TIMER_BASE 0x3F003000UL
#define TIMER_CS   (*(volatile uint32_t*)(BCM2835_TIMER_BASE + 0x00)) // 控制/状态寄存器
#define TIMER_CLO  (*(volatile uint32_t*)(BCM2835_TIMER_BASE + 0x04)) // 当前计数值（低32位）
#define TIMER_C1   (*(volatile uint32_t*)(BCM2835_TIMER_BASE + 0x10)) // 比较寄存器1
#define IRQ_ENABLE1 (*(volatile uint32_t*)(0x3F00B210)) // IRQ Enable 1寄存器

namespace kernel {
namespace driver {
namespace arm64 {

// 初始化 BCM2835 System Timer
void bcm2835_timer_init() {
    uint32_t now = TIMER_CLO;
    uint32_t interval = 1000000 / kernel::TIMER_FREQ; // 1MHz / 频率
    printf("[bcm2835_timer_init] now %d interval %d \n", now, interval);
    TIMER_C1 = now + interval; // 根据频率设置间隔
    TIMER_CS = (1 << 1);    // 清除定时器1中断标志
    IRQ_ENABLE1 = (1 << 1); // 使能 System Timer 1 中断
    printf("[bcm2835_timer_init] TIMER_C1=0x%x, TIMER_CS=0x%x, IRQ_ENABLE1=0x%x\n", TIMER_C1, TIMER_CS, IRQ_ENABLE1);
    printf("[bcm2835_timer_init] done\n");
}

// BCM2835 System Timer 中断处理函数
void bcm2835_timer_interrupt_handler() {
    // 检查是否为定时器1中断
    if (TIMER_CS & (1 << 1)) {
        TIMER_CS = (1 << 1); // 清除中断标志
        uint32_t interval = 1000000 / kernel::TIMER_FREQ; // 1MHz / 频率
        TIMER_C1 = TIMER_CLO + interval; // 根据频率设置下次间隔
        kernel::print("[bcm2835] 时钟中断，调度...\n");
        // kernel::yield(); // 触发调度（如有实现）
    }
}

}
}
} // namespace kernel 