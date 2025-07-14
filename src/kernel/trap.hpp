#pragma once
#include <stdint.h>

namespace kernel {

// 平台无关 trap 号定义
enum TrapCause {
    TRAP_TIMER,      // 时钟中断
    TRAP_SYSCALL,    // 系统调用
    TRAP_EXTERNAL,   // 外部中断
    TRAP_UNKNOWN     // 未知异常
};

// 平台无关 trap 上下文结构体
struct TrapContext {
    uint64_t pc;           // 异常发生时的程序计数器
    uint64_t sp;           // 栈指针
    uint64_t regs[32];     // 通用寄存器（按需裁剪）
    uint64_t cause;        // trap 号
    uint64_t value;        // 附加信息（如错误码等）
};

// 平台无关 trap 处理接口
void trap_handler(TrapContext& ctx);

} // namespace kernel 