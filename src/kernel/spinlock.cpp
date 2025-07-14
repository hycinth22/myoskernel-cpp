#include "spinlock.hpp"
namespace kernel {

void spinlock_init(spinlock* lk) {
    lk->locked = 0;
}
#if defined(__aarch64__)
// ARM64 平台下的自旋锁实现

void spinlock_acquire(spinlock* lk) {
    while (true) {
        unsigned int locked;
        asm volatile("ldaxr %w0, [%1]" : "=r"(locked) : "r"(&lk->locked) : "memory"); // 原子加载lk->lockedd
        if (locked == 0) {
            int fail;
            asm volatile("stlxr %w0, %w2, [%1]"
                         : "=&r"(fail)
                         : "r"(&lk->locked), "r"(1)
                         : "memory"); // 尝试原子存储1到锁变量
            if (fail == 0) {
                return; // 成功获得锁
            }
        }
        // 等待事件，降低功耗
        asm volatile("wfe");
    }
}

void spinlock_release(spinlock* lk) {
    
    asm volatile("stlr wzr, [%0]" : : "r"(&lk->locked) : "memory"); // 原子设置锁状态
    asm volatile("sev"); // 唤醒休眠的其它CPU
}

#else
// x86_64 平台下的自旋锁实现

void spinlock_acquire(spinlock* lk) {
    while (__sync_lock_test_and_set(&lk->locked, 1)) { }
}

void spinlock_release(spinlock* lk) {
    __sync_lock_release(&lk->locked);
}
#endif

} // namespace kernel