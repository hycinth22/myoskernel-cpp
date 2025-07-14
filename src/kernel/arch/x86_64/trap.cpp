// arch/x86_64/trap.cpp
// x86-64 中断/异常处理
#include "../../trap.hpp"
#include "../../panic.hpp"
#include "../../common.hpp"
#include "../../arch_interface.hpp"

namespace kernel {
namespace arch {

struct IDTEntry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t  ist;
    uint8_t  type_attr;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t zero;
} __attribute__((packed));

struct IDTPointer {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

IDTEntry idt[256];
extern "C" void isr_timer();
extern "C" void isr_default();
void set_idt_entry(int vec, void (*handler)()) {
    uint64_t addr = (uint64_t)handler;
    idt[vec].offset_low  = addr & 0xFFFF;
    idt[vec].selector    = 0x08;
    idt[vec].ist         = 0;
    idt[vec].type_attr   = 0x8E;
    idt[vec].offset_mid  = (addr >> 16) & 0xFFFF;
    idt[vec].offset_high = (addr >> 32) & 0xFFFFFFFF;
    idt[vec].zero        = 0;
}
extern "C" void idt_load(IDTPointer*);


void trap_init() {
    for (int i = 0; i < 256; ++i)
        set_idt_entry(i, isr_default);
    set_idt_entry(32, isr_timer); // 32号为PIT时钟中断
    IDTPointer idtp;
    idtp.limit = sizeof(idt) - 1;
    idtp.base = (uint64_t)idt;
    idt_load(&idtp);
    asm volatile ("sti");
    kernel::print("[x86_64] trap_init: IDT已加载，时钟中断已启用\n");
}
} // namespace arch
} // namespace kernel

extern "C" void timer_handler() {
    kernel::print("[x86_64] 时钟中断，调度...\n");
    kernel::yield();
    uint8_t eoi = 0x20;
    asm volatile ("outb %0, %1" : : "a"(eoi), "Nd"((uint16_t)0x20));
}
extern "C" void default_handler() {
    kernel::print("[x86_64] 未处理的中断/异常\n");
    while (1) { asm volatile ("hlt"); }
}
extern "C" void trap_entry(uint64_t pc, uint64_t sp, uint64_t cause, uint64_t value) {
    kernel::TrapContext ctx = {};
    ctx.pc = pc;
    ctx.sp = sp;
    ctx.cause = cause;
    ctx.value = value;
    // TODO: 填充 ctx.regs[] 
    kernel::trap_handler(ctx);
}
