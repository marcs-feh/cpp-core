#include "bump_allocator.hpp"

using bp = BumpAllocator;

bp::BumpAllocator(byte* buf, usize bufsize) : off{0} {
}

