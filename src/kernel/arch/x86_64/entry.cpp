// arch/x86_64/entry.cpp
// x86-64 架构相关入口，负责初始化并跳转到内核主入口
#include "../../common.hpp"
extern "C" void arch_entry() {
    kernel::main(0);
    __asm__("hlt");
}