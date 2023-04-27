// Assert allows to break the program when some condition has not been
// fulfilled, asserts may be disabled with the ASSERT_DISABLE macro. Panics are
// similar, however, they are unaffected by ASSERT_DISABLE. This file disables
// the `assert()` macro if it exists.

#ifndef _assert_hpp_include_
#define _assert_hpp_include_

#undef assert

#include <cstdio>
#include <cstdlib>

// Breaks the program
#define Break() { std::abort(); }

static inline constexpr
void assert(bool cond, const char* msg = nullptr){
#if !(defined(NDEBUG) || defined(ASSERT_DISABLE))
	if(cond){ return; }
	msg = msg ? msg : "(no message)";
	std::fprintf(stderr, "[Assert Fail]: %s\n", msg);
	Break();
#endif
}

static inline
void panic(const char* msg = nullptr){
	msg = msg ? msg : "(no message)";
	std::fprintf(stderr, "[Panic]: %s\n", msg);
	Break();
}

static inline constexpr
void panicAssert(bool cond, const char* msg = nullptr){
	if(cond){ return; }
	panic(msg);
	Break();
}

#undef Break
#endif /* Include guard */
