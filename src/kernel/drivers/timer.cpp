// kernel/drivers/timer.cpp
// 平台无关定时器接口
#include "../common.hpp"
#include "../arch_interface.hpp"

namespace kernel {
namespace driver {

    // 定时器初始化
    void timer_init() {
    #if defined(__x86_64__)
        x86_64::pit_init();
    #elif defined(__aarch64__)
        arm64::bcm2835_timer_init();
    #endif
    }
}}