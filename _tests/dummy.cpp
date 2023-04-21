#ifndef _dummy_cpp_include_
#define _dummy_cpp_include_

#include "types.hpp"
// Dummy classes for testing move semantics activation.
struct A {
	static uint ctorUses;
	static uint dtorUses;
	static uint copyCtorUses;
	static uint moveCtorUses;
	static uint copyAssUses;
	static uint moveAssUses;

	int* p;

	static void reset() {
		A::ctorUses     = 0;
		A::dtorUses     = 0;
		A::copyCtorUses = 0;
		A::moveCtorUses = 0;
		A::copyAssUses  = 0;
		A::moveAssUses  = 0;
	}

	A(){ A::ctorUses += 1; }
	A(const A&){ A::copyCtorUses += 1;}
	A(A&&){ A::moveCtorUses += 1;}
	void operator=(const A&){ A::copyAssUses += 1;}
	void operator=(A&&){ A::moveAssUses += 1;}
	~A(){ A::dtorUses += 1; }
};

uint A::ctorUses     = 0;
uint A::dtorUses     = 0;
uint A::copyCtorUses = 0;
uint A::moveCtorUses = 0;
uint A::copyAssUses  = 0;
uint A::moveAssUses  = 0;

#endif /* Include guard */
