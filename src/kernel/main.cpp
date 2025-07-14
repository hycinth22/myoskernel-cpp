// kernel/main.cpp
// 内核主入口，初始化各子系统并启动shell
#include "common.hpp"
#include "arch_interface.hpp"

namespace kernel {
    void uart_init();
    void clock_init();
    void proc_init();
    void shell_main();
    void smp_init();

    // 内核主入口
    void main(int cpu_id) {
        uart_init();
        printf("cpu %d enter main... \n", cpu_id);
        // trap_init();
        clock_init();
        proc_init();
        // smp_init();

        if (cpu_id == 0) {
            print("\n==============================\n");
            print("  Kernel has been started (on CPU0) ");
            print(")\n==============================\n");
            shell_main();
        } else {
            print("  Kernel has been started (on CPU%d)\n", cpu_id);
        }
        // 其他核进入idle
        arch::arch_idle();
    }
} 