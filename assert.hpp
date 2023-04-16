#ifndef _assert_hpp_include_
#define _assert_hpp_include_

// Convert something to `do {} while(0)` form, this is due to weird eval rules of C/C++
#define As_Statement(S) do { S ; } while(0);

#include <cstdio>
#include <cstdlib>
// Breaks the program with an optional message
#define Assert_Break(M) { fprintf(stderr, "Failed assertion: %s\n", M); std::abort(); }

#ifdef ASSERT_ENABLE
# define Assert(E) As_Statement(if(!(E)){Assert_Break(#E);})
#else
# define Assert(E)
#endif

#endif /* Include guard */
