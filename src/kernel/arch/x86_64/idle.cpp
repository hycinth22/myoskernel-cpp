#include "../../common.hpp"
namespace kernel {
    namespace arch {
        void arch_idle() { while (1) { __asm__("hlt"); } }
}}