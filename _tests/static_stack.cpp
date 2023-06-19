#include "test/test.hpp"
#include "struct/static_stack.hpp"

using namespace core;
void test_staticStack(){
	Test T("Static Stack");
	{
		StaticStack<int, 20> stk;
		Tp(stk.cap() == 20);
	}
}
