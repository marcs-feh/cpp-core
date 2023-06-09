// Assert allows to break the program when some condition has not been
// fulfilled, asserts may be disabled with the ASSERT_DISABLE macro. Panics are
// similar, however, they are unaffected by ASSERT_DISABLE. This file replaces
// the standard assert() macro if OVERRIDE_ASSERT_MACRO is defined.

#ifndef _assert_hpp_include_
#define _assert_hpp_include_

#include <cstdio>
#include <cstdlib>

namespace core {

// Breaks the program, define this to your liking
#define Break() { std::abort(); }

#if defined(RELEASE_MODE)
#undef ASSERT_DISABLE
#define ASSERT_DISABLE
#endif

#if !defined(ASSERT_DISABLE)
#define Assert(x_, msg_) core::assert_expr((x_), "(" #x_ ") <- " msg_)
#else
#define Assert(x_, msg_)
#endif

#if defined(OVERRIDE_ASSERT_MACRO)
#undef assert
#define assert(x_, msg_) core::assert_expr((x_), "(" #x_ ") <- " msg_)
#endif

#define Panic_Assert(x_, msg_) core::panic_assert((x_), "(" #x_ ") <- " msg_)

static inline constexpr
void assert_expr([[maybe_unused]] bool cond, [[maybe_unused]] const char* msg = nullptr){
	if(cond){ return; }
	msg = msg ? msg : "(no message)";
	std::fprintf(stderr, "[Assert Fail]: %s\n", msg);
	Break();
}

static inline
void panic(const char* msg = nullptr){
	msg = msg ? msg : "(no message)";
	std::fprintf(stderr, "[Panic]: %s\n", msg);
	Break();
}

static inline constexpr
void panic_assert(bool cond, const char* msg = nullptr){
	if(cond){ return; }
	panic(msg);
	Break();
}

}

#undef Break
#endif /* Include guard */
