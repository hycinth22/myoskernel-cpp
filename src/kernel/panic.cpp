#include "panic.hpp"
#include "printf.hpp"
#include "arch_interface.hpp"

namespace kernel {

[[noreturn]] void panic(const char* msg) {
    printf("[panic] : %s\n", msg);
    // 死循环停机，防止继续执行
    while (1) {
        arch::arch_idle();
    }
    __builtin_unreachable();
}

} // namespace kernel 