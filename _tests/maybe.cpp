#include "test/test.hpp"
#include "_tests/dummy.cpp"
#include "maybe.hpp"

void test_maybe(){
	Test T("Maybe");
	// Default init
	{
		A::reset();
		Maybe<A> a;
		Tp(!a.ok());
		Tp(A::ctorUses == 0);
	}
	// Constructing Maybe
	{
		A::reset();
		A x;
		A y;
		Maybe<A> a(move(x));
		Maybe<A> b(y);
		Tp(a.ok());
		Tp(A::moveCtorUses == 1);
		Tp(A::copyCtorUses == 1);
	}
	// Conditional destructor
	{
		{
			A::reset();
			Maybe<A> x((A())); // 2 dtor, one for x, one for tmp
			Maybe<A> y; // No dtor
		}
		Tp(A::dtorUses == 2);
	}
	// Moving and copying to maybe
	{
		A::reset();
		Maybe<A> x;
		Tp(A::ctorUses == 0);
		x = A();
		Tp(x.ok());
		Tp(A::ctorUses == 1);
		Tp(A::moveCtorUses == 1);
		x = A();
		Tp(x.ok());
		Tp(A::moveAssUses == 1);
	}
	{
		A::reset();
		Maybe<A> x;
		A a;
		Tp(A::ctorUses == 1);
		x = a;
		Tp(x.ok());
		Tp(A::ctorUses == 1);
		Tp(A::copyCtorUses == 1);
		x = a;
		Tp(x.ok());
		Tp(A::copyAssUses == 1);
	}
	// Getting things out of maybe
	{
		Maybe<int> n(69);
		Tp(n.ok());
		int x = n.get();
		Tp(x == 69);
		Tp(!n.ok());
		Tp(n.getOr(x))
	}
}

