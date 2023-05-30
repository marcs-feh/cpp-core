#include "struct/static_list.hpp"
#include "test/test.hpp"
#include "dummy.cpp"
#include <iostream>

using namespace core;


template<typename T, usize N>
void print_list(const StaticList<T, N>& l) {
	std::cout << "[ ";
	for(usize i = 0; i < l.len(); i += 1){
		std::cout << l[i] << " ";
	}
	std::cout << "]\n";
}

void test_staticList(){
	Test T("Static List");
	{
	StaticList<int, 8> l;
	Tp(l.len() == 0);
	Tp(l.cap() == 8);
	l.push(69);
	Tp(l.len() == 1);
	Tp(l.at(0) == 69);
	l[0] = 420;
	Tp(l.at(0) == 420);
	l.pop();
	Tp(l.len() == 0);
	l.pop(); l.pop(); l.pop();
	Tp(l.len() == 0);
	}
	{
		A::reset();
		StaticList<A, 4> l;
		Tp(A::ctorUses == 0);
		auto a = A();
		l.push(a);
		Tp(A::ctorUses == 1);
		Tp(A::copyCtorUses == 1);
		l.push(move(a));
		Tp(A::moveCtorUses == 1);
		A::reset();
		l.pop();
		Tp(A::dtorUses == 1);
	}
	{
		StaticList<int, 6> l0;
		StaticList<int, 6> l1;
		print_list(l0);
		l0.push(4); l0.push(2); l0.push(0);
		l1.push(4); l1.push(2); l1.push(0);
		Tp(l0 == l1);
		l0.insert(6, 0);
		l0.insert(9, 1);
		Tp(l0[0] == 6); Tp(l0[1] == 9);
		Tp(l0 != l1);
		l1.insert(1, 0);
		l1.insert(2, 1);
		Tp(l0 != l1);
		print_list(l0);
	}
}
