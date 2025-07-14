// kernel/mm.cpp
// 物理内存管理，目前仅支持简单页分配（无回收）
#include "common.hpp"

namespace kernel {
    constexpr size_t PAGE_SIZE = 4096;
    constexpr size_t MAX_MEM   = 4ULL * 1024 * 1024 * 1024; // 4GB
    constexpr size_t MAX_PAGES = MAX_MEM / PAGE_SIZE;       // 支持4GB物理内存
    static uint8_t page_bitmap[MAX_PAGES] = {0};
    static uint8_t* base = (uint8_t*)0x100000;

    // 初始化物理内存管理
    void mm_init() {
        for (size_t i = 0; i < MAX_PAGES; ++i) page_bitmap[i] = 0;
        print("[mm] 物理内存管理已初始化\n");
    }

    // 分配物理内存
    void* alloc_page() {
        for (size_t i = 0; i < MAX_PAGES; ++i) {
            if (!page_bitmap[i]) {
                page_bitmap[i] = 1;
                return base + i * PAGE_SIZE;
            }
        }
        print("[mm] 内存不足！\n");
        return nullptr;
    }

    // 释放物理内存
    void free_page(void* addr) {
        size_t idx = ((uint8_t*)addr - base) / PAGE_SIZE;
        if (idx < MAX_PAGES) page_bitmap[idx] = 0;
        // TODO: 实现回收
    }
}

extern "C" void* kmalloc(size_t size) {
    if (size > kernel::PAGE_SIZE) return nullptr;
    return kernel::alloc_page();
}
extern "C" void kfree(void* ptr) {
    kernel::free_page(ptr);
}

extern "C" void* memset(void* s, int c, size_t n) {
    unsigned char* p = (unsigned char*)s;
    while (n--) *p++ = (unsigned char)c;
    return s;
}