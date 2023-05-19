#ifndef _complex_cpp_include_
#define _complex_cpp_include_

#include "test/test.hpp"
#include "complex.hpp"
using namespace core;

void test_complex(){
	Test T("Complex");
	{
		using Cx = Complex64;
		Cx a = {5, 9};
		Cx b = {3, -1};

		Cx add = a + b;
		Cx sub = a - b;
		Cx mul = a * b;
		Cx div = a / b;

		Tp(add == Cx(8,8));
		Tp(sub == Cx(2,10));
		Tp(mul == Cx(24,22));
		Tp(div == Cx(0.6, 3.2));
	}
	{
		using Cx = Complex128;
		Cx a = {5, 9};
		Cx b = {3, -1};

		Cx add = a + b;
		Cx sub = a - b;
		Cx mul = a * b;
		Cx div = a / b;

		Tp(add == Cx(8,8));
		Tp(sub == Cx(2,10));
		Tp(mul == Cx(24,22));
		Tp(div == Cx(0.6, 3.2));
	}
	{
		Tp(abs(Complex64(3, 4)) == 5);
		Tp(abs(Complex128(3, 4)) == 5);
	}
}

#endif /* Include guard */
