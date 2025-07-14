// kernel/drivers/uart.cpp
// 平台无关串口接口
#include "../common.hpp"
#include "../spinlock.hpp"

#if defined(__x86_64__)
extern void uart_init_x86();
extern void uart_putc_x86(char c);
#endif
#if defined(__aarch64__)
extern void uart_init_arm();
extern void uart_putc_arm(char c);
#endif

namespace kernel {
    static spinlock uart_lock;
    void uart_init() {
    #if defined(__x86_64__)
        uart_init_x86();
    #elif defined(__aarch64__)
        uart_init_arm();
    #endif
        spinlock_init(&uart_lock);
    }
    void print(const char* str) {
        print(str, strlen(str));
    }
    void print(const char* str, size_t len) {
        spinlock_acquire(&uart_lock);
    #if defined(__x86_64__)
        for (size_t i = 0; i < len; ++i) {
            if (str[i]) uart_putc_x86(str[i]);
        }
    #elif defined(__aarch64__)
        for (size_t i = 0; i < len; ++i) {
            if (str[i]) uart_putc_arm(str[i]);
        }
    #endif
        spinlock_release(&uart_lock);
    }
} 