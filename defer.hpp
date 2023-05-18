// The Defer macro allows you to create a block of code that is deffered to the
// end of the scope. Due to template deduction rules, the `Defer` macro is only
// available on C++17 or above.

#ifndef _defer_hpp_include_
#define _defer_hpp_include_

#include "utils.hpp"

namespace defer_impl {
template<typename F>
struct Call {
	F fn;

	Call(F&& fn) : fn(move(fn)){}
	~Call(){ fn(); }
};
template<typename F>
Call<F> wrapFunc(F&& f){
	return Call<F>(forward<F>(f));
}
}

#define Defer_Concat0(x, y) x##y
#define Defer_Concat1(x, y) Defer_Concat0(x, y)
#define Defer_ConcatN(x) Defer_Concat1(x, __COUNTER__)
#define Defer \
	static_assert(__cplusplus >= 201703L, "Defer macro is only supported for C++17 or newer."); \
	defer_impl::Call Defer_ConcatN(_defer_tmp_) = [&]()

#endif /* Include guard */
