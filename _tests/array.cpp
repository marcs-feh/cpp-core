#include "array.hpp"
#include "test/test.hpp"

using namespace core;

void test_array(){
	Test T("Array");
	auto arr = Array<int, 3>{69, 0, 420};
	Tp(arr.len() == 3);
	Tp(arr[0] == 69);
	Tp(arr[1] == 0);
	Tp(arr[2] == 420);
	Tp(arr.at(0) == 69);
	Tp(arr.at_or(0, 20) == 69);
	Tp(arr.at_or(5, 20) == 20);
}
