#include "defer.hpp"
#include "test/test.hpp"
using namespace core;

void test_defer(){
	Test T("Defer");

	int x = 69;
	{
		Defer { x = 420; };
		Tp(x == 69);
	}
	Tp(x == 420);

	#if __cplusplus >= 201703L

	int y = 42;
	int z = 0;
	{
		y = 0;
		Defer {
			z = (y * 2) + 1;
		};
		y = 34;
		Tp(z == 0);
	}
	Tp(z == 69);

	#endif
}
