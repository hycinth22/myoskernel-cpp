#pragma once
#include <stdint.h>

namespace kernel {

void clock_init();
uint64_t clock_ticks();
void clock_interrupt();

} // namespace kernel 