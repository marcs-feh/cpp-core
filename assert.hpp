// Assert allows to break the program when some condition has not been
// fulfilled, asserts may be disabled with the ASSERT_DISABLE macro. Panics are
// similar, however, they are unaffected by ASSERT_DISABLE.

#ifndef _assert_hpp_include_
#define _assert_hpp_include_

#include <cstdio>
#include <cstdlib>

// Convert something to `do {} while(0)` form, this is due to weird eval rules of C/C++
#define As_Statement(S) do { S ; } while(0);

// Breaks the program
#define Break() { std::abort(); }

#define Assert(E, M)                                                           \
  As_Statement(if (!(E)) {                                                     \
    fprintf(stderr, "[Assert: %s] Failed: %s\n", #E, M);                       \
    Break();                                                                   \
  })

// Stops the program with a fatal error, this is unaffected by ASSERT_DISABLE
#define Panic(M)                                                               \
  {                                                                            \
    fprintf(stderr, "[Panic] %s\n", M);                                        \
    Break();                                                                   \
  }

#define Panic_Assert(E, M)                                                     \
  As_Statement(if (!(E)) {                                                     \
    fprintf(stderr, "[Panic] %s\n", M);                                        \
    Break();                                                                   \
  })

#ifdef ASSERT_DISABLE
#undef Assert
#define Assert(E, M)
#endif

#endif /* Include guard */
