#pragma once
namespace kernel {
struct spinlock {
    volatile int locked;
};
void spinlock_init(spinlock* lk);
void spinlock_acquire(spinlock* lk);
void spinlock_release(spinlock* lk);
} 