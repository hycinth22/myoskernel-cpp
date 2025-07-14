// kernel/shell.cpp
// shell实现，目前仅支持内建命令
#include "common.hpp"
#include "arch_interface.hpp"

namespace kernel {
#if defined(__x86_64__)
    // x86-64串口输入辅助函数
    static uint8_t inb(uint16_t port) {
        uint8_t ret;
        asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
        return ret;
    }
#endif

#if defined(__aarch64__)
    // 支持 QEMU virt 板和树莓派3b
    #define UART_RPI3B  0x3F201000
    #define UART_VIRT   0x09000000
    static uintptr_t uart_base = UART_RPI3B;
    // 应该运行时判断（如通过设备树或启动参数），这里只用编译时宏
#endif

    // 串口输入（阻塞，回显）
    static char getchar() {
    #if defined(__x86_64__)
        uint16_t port = 0x3F8;
        while ((inb(port + 5) & 1) == 0);
        char c = inb(port);
        print(&c, 1); // 回显
        return c;
    #elif defined(__aarch64__)
        while (*(volatile uint32_t*)(uart_base + 0x18) & (1 << 4));
        char c = *(volatile uint32_t*)(uart_base + 0x00) & 0xFF;
        print(&c, 1);
        return c;
    #else
        return 0;
    #endif
    }

    // 读取一行输入（阻塞，回显）
    static void getline(char* buf, size_t maxlen) {
        size_t i = 0;
        while (i + 1 < maxlen) {
            char c = getchar();
            if (c == '\r' || c == '\n') {
                print("\r\n");
                break;
            }
            if (c == '\b' || c == 127) { // 退格
                if (i > 0) {
                    --i;
                    print("\b \b", 3);
                }
                continue;
            }
            buf[i++] = c;
        }
        buf[i] = 0;
    }

    void shell_main() {
        const char* prompt = "imnotaos> ";
        char buf[128];
        while (1) {
            print(prompt);
            getline(buf, sizeof(buf));
            if (strcmp(buf, "help") == 0) {
                print("支持命令: help, echo, exit\n");
            } else if (strncmp(buf, "echo ", 5) == 0) {
                print(buf + 5);
                print("\n");
            } else if (strcmp(buf, "exit") == 0) {
                print("goodbye~\n");
                arch::poweroff();
                break;
            } else if (strcmp(buf, "") == 0) {
                // 空行
            } else {
                print("未知命令: ");
                print(buf);
                print("\n");
            }
        }
    }
} 