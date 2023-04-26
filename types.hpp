// General type definitions

#ifndef _types_hpp_include_
#define _types_hpp_include_

#include <stdint.h>
#include <stddef.h>
#include <stdalign.h>

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using f32 = float;
using f64 = double;

using uint    = unsigned int;
using byte    = uint8_t;
using rune    = uint32_t;
using uintptr = uintptr_t;
using usize   = size_t;
#ifndef NO_SIGNED_SIZE
static_assert(sizeof(ptrdiff_t) == sizeof(size_t),
              "Could not find suitable ssize. Use NO_SIGNED_SIZE to disable it.");
using ssize   = ptrdiff_t;
#endif

// Needed so the compiler doesnt cry about it
void* operator new(usize, void*) noexcept;

#endif /* Include guard */
