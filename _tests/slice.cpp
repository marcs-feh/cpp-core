#ifndef _slice_cpp_include_
#define _slice_cpp_include_

#include "test/test.hpp"
#include "slice.hpp"

void test_slice(){
	Test T("Slice");

	char m[] = "Hey bro, nice balls";
	char n[] = "What? Hey bro!";

	auto s0 = Slice<char>(m, 3);
	auto s1 = Slice<char>(&n[6], 3);

	Tp(s0.len() == 3);
	Tp(s1.len() == 3);
	Tp(s0 == s1);

	s0 = move(s1);

	Tp(s1.null() && !s0.null());
	Tp(!s1 && s0);
	Tp(s0);
}


#endif /* Include guard */
