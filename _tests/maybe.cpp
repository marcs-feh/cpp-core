#include "test/test.hpp"
#include "_tests/dummy.cpp"
#include "maybe.hpp"


void test_maybe(){
	Test T("Maybe");
	[[maybe_unused]]
	auto div = [](int a, int b) -> Maybe<int> {
		Maybe<int> res;
		if(b == 0){ return res; }
		res = a / b;
		return res;
	};
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
		int x = move(n).get();
		Tp(x == 69);
		Tp(!n.ok());
		Tp(n.getOr(x))
	}
	// Destroy
	{
		A::reset();
		Maybe<A> a;
		a = A();
		Tp(a.ok());
		a.destroy();
		Tp(!a.ok());
	}
	// Const
	{
		const Maybe<int> x(420);
		Tp(x.get() == 420);
		Tp(x.getOr(69) == 420);
		const Maybe<int> y;
		Tp(y.getOr(69) == 69);
	}
	// Maybe =
	{
		A::reset();
		Maybe<A> a;
		Maybe<A> b((A()));
		Tp(!a && b);
		b = a;
		Tp(!a && !b);
		Tp(A::copyAssUses == 0);
	}
	{
		A::reset();
		Maybe<A> a;
		Maybe<A> b((A()));
		Tp(!a && b);
		a = b;
		Tp(a && b);
		Tp(A::copyCtorUses == 1);
	}
	{
		A::reset();
		Maybe<A> a((A()));
		Maybe<A> b((A()));
		a = b;
		Tp(A::copyAssUses == 1);
	}
	{
		A::reset();
		Maybe<A> a((A()));
		Maybe<A> b((A()));
		Tp(a && b);
		a = move(b);
		Tp(a && !b);
		Tp(A::moveAssUses == 1);
	}
}

