#include "test/test.hpp"
#include "struct/static_stack.hpp"

using namespace core;
void test_staticStack(){
	Test T("Static Stack");
	{
		StaticStack<int, 8> stk;
		Tp(0 == stk.len());
		Tp(8 == stk.cap());
		stk.push(9);
		stk.push(6);
		int x;
		Tp(stk.top().get() == 6);
		stk.pop(x);
		Tp(x == 6);

		Tp(stk.top().get() == 9);
		stk.pop(x);
		Tp(x == 9);

		Tp(!stk.top());
	}
}
