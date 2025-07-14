// arch/arm64/smp.cpp
// ARM64 多核支持

#include "../../common.hpp"
#include "../arch.hpp"

namespace kernel {

static inline int get_cpu_id() {
    uint64_t mpidr;
    asm volatile ("mrs %0, mpidr_el1" : "=r"(mpidr));
    return mpidr & 0xff;
}

static uint64_t psci_cpu_on(uint64_t target_cpu, uint64_t entry, uint64_t context) {
    register uint64_t x0 asm("x0") = 0x84000003; // PSCI_CPU_ON
    register uint64_t x1 asm("x1") = target_cpu;
    register uint64_t x2 asm("x2") = entry;
    register uint64_t x3 asm("x3") = context;
    asm volatile("smc #0" : "+r"(x0) : "r"(x1), "r"(x2), "r"(x3));
    return x0;
}

void smp_init() {
    int cpu_id = get_cpu_id();
    printf("[arm64] smp_init: CPU %d\n", cpu_id);
}

} // namespace kernel 