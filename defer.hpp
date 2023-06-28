// The Defer macro allows you to create a block of code that is deffered to the
// end of the scope.

#ifndef _defer_hpp_include_
#define _defer_hpp_include_

#include "utils.hpp"

namespace core {
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
}

#define _impl_Defer_Concat0(X_, Y_) X_##Y_
#define _impl_Defer_Concat1(X_, Y_) _impl_Defer_Concat0(X_, Y_)
#define _impl_Defer_ConcatN(X_)     _impl_Defer_Concat1(X_, __COUNTER__)
#define Defer(SRC_) \
	auto _impl_Defer_ConcatN(_defer_tmp_) = defer_impl::wrapFunc([&](){ SRC_ ; })

#endif /* Include guard */
