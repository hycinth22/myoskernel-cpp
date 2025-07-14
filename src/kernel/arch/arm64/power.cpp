#include <stdint.h>

namespace kernel {
    namespace arch {
    

void poweroff() {
    *((volatile uint32_t*)0x3c000000) = 0x5555;
    while (1) { asm volatile("wfe"); }
}

}}