#ifndef _vec_cpp_include_
#define _vec_cpp_include_

#include "vec/vec.hpp"
#include "test/test.hpp"

template<usize N>
using Vec = vec::VecN<f64, N>;

void test_vec(){
	Test T("Vec");
}

#endif /* Include guard */
