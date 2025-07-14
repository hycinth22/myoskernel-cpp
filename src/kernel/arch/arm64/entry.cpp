// arch/arm64/entry.cpp
// ARM64 架构相关入口，负责初始化并跳转到内核主入口
#include "../../common.hpp"

static inline int get_cpu_id() {
    uint64_t mpidr;
    asm volatile ("mrs %0, mpidr_el1" : "=r"(mpidr));
    return mpidr & 0xff;
}

extern "C" void arch_entry() {
    int cpu_id = get_cpu_id();
    kernel::main(cpu_id);
    while (1) __asm__("wfe");
} 