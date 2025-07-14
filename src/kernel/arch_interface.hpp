namespace kernel {
    namespace arch {
        extern void trap_init();
        extern void poweroff();
        extern void arch_idle();
    }
    namespace driver {
        extern void timer_init();
        namespace x86_64 {
            void pit_init();
        }
        namespace arm64 {
            extern void generic_timer_init();
            extern void generic_timer_interrupt_handler();
            extern void bcm2835_timer_init();
            extern void bcm2835_timer_interrupt_handler();
        }
    }
}