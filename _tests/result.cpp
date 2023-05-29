#include "test/test.hpp"
#include "result.hpp"
#include "dummy.cpp"

using namespace core;

void test_result(){
	struct Error { int code = 69; };
	Test T("Result");
	{
		A::reset();
		Result<A, Error> r;
		Tp(!r.ok());
		Tp(r.err().code == 69);
		Tp(A::ctorUses == 0);
	}
	{
		A::reset();
		Result<A, Error> r((Error()));
		Tp(!r.ok());
		Tp(A::ctorUses == 0);
		Tp(A::moveCtorUses == 0);
	}
	{
		A::reset();
		Result<A, Error> r((A()));
		Tp(r.ok());
		Tp(A::ctorUses == 1);
		Tp(A::moveCtorUses == 1);
	} Tp(A::dtorUses == 2);
	{
		A::reset();
		Result<A, Error> r((Error()));
		Tp(!r.ok());
		r = A();
		Tp(r.ok());
		Tp(A::moveCtorUses == 1);
	}
	{
		A::reset();
		Result<A, Error> r((Error()));
		r = Result<A, Error>(A());
		Tp(r.ok());
		Tp(A::moveCtorUses == 2);
		r = Result<A, Error>(Error());
		Tp(!r.ok());
	}
	{
		Result<int, Error> r;
		r = 420;
		Tp(r.get_or(69) == 420);
		auto e = Error();
		r = e;
		Tp(r.get_or(69) == 69);
	}
}
