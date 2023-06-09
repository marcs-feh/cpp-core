// This file defines a global allocator that serves as the default choice for
// dynamic structures. This allocator should be preferably LibC allocator

#ifndef _default_allocator_hpp_include_
#define _default_allocator_hpp_include_

#include "mem/allocator.hpp"
#include "mem/libc_allocator.hpp"

namespace core {
inline auto default_allocator = LibcAllocator();
}

#endif /* Include guard */
