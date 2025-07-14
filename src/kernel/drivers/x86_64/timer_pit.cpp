#include "../../common.hpp"
#if defined(__x86_64__)
static constexpr uint16_t COM1_PORT = 0x3F8;
static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

namespace kernel {
namespace driver {
namespace x86_64 {

void pit_init() {
    uint32_t freq = 100;
    uint16_t divisor = 1193180 / freq;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);
}

}}}
#endif 