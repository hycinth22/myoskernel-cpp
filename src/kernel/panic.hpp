#pragma once

#include <stdnoreturn.h>

namespace kernel {

[[noreturn]] void panic(const char* msg);

} // namespace kernel 