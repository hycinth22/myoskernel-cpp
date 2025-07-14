// kernel/proc.cpp
// 多进程/调度器实现，简单轮转调度
#include "common.hpp"

namespace kernel {
    constexpr int MAX_PROC = 8;
    enum class State { UNUSED, RUNNABLE, RUNNING, ZOMBIE };
    struct Context {
        uint64_t rsp;
        void (*rip)();
    };
    struct Proc {
        State state;
        Context ctx;
        int pid;
        char name[16];
        uint8_t* stack;
    };
    static Proc procs[MAX_PROC];
    static int current = 0;
    static int next_pid = 1;

    extern "C" void switch_context(Context* old, Context* newc);

    int create_kernel_thread(void (*entry)(), const char* name) {
        for (int i = 0; i < MAX_PROC; ++i) {
            if (procs[i].state == State::UNUSED) {
                procs[i].state = State::RUNNABLE;
                procs[i].ctx.rip = entry;
                procs[i].stack = new uint8_t[4096]();
                procs[i].ctx.rsp = (uint64_t)(procs[i].stack + 4096 - 8);
                ((void(**)())(procs[i].ctx.rsp))[0] = entry;
                procs[i].pid = next_pid++;
                for (int j = 0; j < 15 && name[j]; ++j) procs[i].name[j] = name[j];
                procs[i].name[15] = 0;
                return procs[i].pid;
            }
        }
        return -1;
    }

    void schedule() {
        int n = current;
        for (int i = 1; i <= MAX_PROC; ++i) {
            int idx = (n + i) % MAX_PROC;
            if (procs[idx].state == State::RUNNABLE) {
                int prev = current;
                procs[prev].state = State::RUNNABLE;
                procs[idx].state = State::RUNNING;
                current = idx;
                switch_context(&procs[prev].ctx, &procs[idx].ctx);
                break;
            }
        }
    }

    void proc_init() {
        for (int i = 0; i < MAX_PROC; ++i) procs[i].state = State::UNUSED;
        procs[0].state = State::RUNNING;
        procs[0].pid = 0;
        procs[0].ctx.rip = nullptr;
        procs[0].ctx.rsp = 0;
        procs[0].name[0] = 'i'; procs[0].name[1] = 'd'; procs[0].name[2] = 'l'; procs[0].name[3] = 'e'; procs[0].name[4] = 0;
        procs[0].stack = nullptr;
        current = 0;
    }

    void yield() {
        schedule();
    }
}
