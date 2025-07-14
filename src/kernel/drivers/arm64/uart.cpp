#include "../../common.hpp"
#if defined(__aarch64__)

#define QEMU_UART0_BASE 0x09000000
#define RASPI3B_UART0_BASE 0x3F201000
#define UART0_BASE RASPI3B_UART0_BASE

#define UART0_DR   (*(volatile uint32_t*)(UART0_BASE + 0x00))
#define UART0_FR   (*(volatile uint32_t*)(UART0_BASE + 0x18))

void uart_init_arm() {

}
void uart_putc_arm(char c) {
    while (UART0_FR & (1 << 5));
    UART0_DR = c;
}
#endif