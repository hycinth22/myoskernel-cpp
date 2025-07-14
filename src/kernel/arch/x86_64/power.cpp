#include<stdint.h>

namespace kernel {
    namespace arch {
    
    void poweroff() {
        asm volatile ("outw %0, %1" : : "a"((uint16_t)0x2000), "Nd"(0x604));
    }

}}