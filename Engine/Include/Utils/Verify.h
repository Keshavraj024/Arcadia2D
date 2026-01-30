#pragma once

#include <cassert>

// clang-format off
#ifdef NDEBUG
    #define VERIFY(expr) void(expr)
#else
    #define VERIFY(expr) assert(expr)
#endif
// clang-format on
