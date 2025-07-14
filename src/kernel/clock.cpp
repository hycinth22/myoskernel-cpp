#include "clock.hpp"
#include "printf.hpp"
#include "arch_interface.hpp"
#include "param.hpp"

namespace kernel {

static volatile uint64_t ticks = 0;

void clock_init() {
    printf("[clock] init...\n");
    ticks = 0;
    driver::timer_init();
    printf("[clock] up.\n");
}

uint64_t clock_ticks() {
    return ticks;
}

void clock_interrupt() {
    ++ticks;
}

} // namespace kernel 