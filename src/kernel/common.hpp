#pragma once
// kernel/common.hpp
// 内核通用类型与工具函数

#include <stddef.h>
#include <stdint.h>
#include "spinlock.hpp"
#include "printf.hpp"
#include "panic.hpp"
#include "param.hpp" // 全局参数头文件

namespace kernel {
    void main(int cpu_id);
    void yield();
    void print(const char* str);
    void print(const char* str, size_t len);

    inline size_t strlen(const char* s) {
        size_t n = 0;
        while (s && s[n]) ++n;
        return n;
    }

    inline int strcmp(const char* a, const char* b) {
        while (*a && (*a == *b)) ++a, ++b;
        return *(const unsigned char*)a - *(const unsigned char*)b;
    }

    inline int strncmp(const char* a, const char* b, size_t n) {
        while (n && *a && (*a == *b)) ++a, ++b, --n;
        if (n == 0) return 0;
        return *(const unsigned char*)a - *(const unsigned char*)b;
    }

    inline void print_uint64(uint64_t val) {
        char buf[32];
        int n = 0;
        if (val == 0) {
            buf[n++] = '0';
        } else {
            char tmp[20]; int t = 0;
            while (val && t < 20) { tmp[t++] = '0' + (val % 10); val /= 10; }
            for (int i = t - 1; i >= 0; --i) buf[n++] = tmp[i];
        }
        buf[n] = 0;
        print(buf);
    }
}

[[noreturn]] inline void unimplemented() {
    kernel::panic("unimplement");
}

extern "C" void* kmalloc(size_t size);
extern "C" void kfree (void* ptr);
inline void* operator new(size_t size) noexcept { return kmalloc(size); }
inline void* operator new[](size_t size) noexcept { return kmalloc(size); }
// inline void operator delete(void* ptr) noexcept { kfree(ptr); }
// inline void operator delete(void*, long unsigned int) noexcept { unimplemented(); }
// inline void operator delete[](void* ptr) noexcept { unimplemented(); }
// inline void operator delete[](void* ptr, size_t n) noexcept { unimplemented(); } 