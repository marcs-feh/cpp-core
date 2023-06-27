#ifndef _test_dyn_array_cpp_include_
#define _test_dyn_array_cpp_include_

#include "struct/dyn_array.hpp"
#include "mem/linear_allocator.cpp"
#include "consts.hpp"
#include "test/test.hpp"

using namespace core;
constexpr auto K = prefix::kibi;

void test_dynArray(){
	Test T("DynArray");
	constexpr auto n = 16 * K;
	auto buf = Slice<byte>(new byte[n], n);
	LinearAllocator al = LinearAllocator(move(buf));
	DynArray a = DynArray<int, LinearAllocator>(&al);
	{
		auto cap = DynArray<int, LinearAllocator>::default_capacity;
		Tp(a.cap() == cap);
		Tp(a.len() == 0);
		Tp(a.data != nullptr);
	}
	{
		bool ok = true;
		ok = ok && a.append(4);
		ok = ok && a.append(2);
		ok = ok && a.append(0);
		Tp(ok);
		Tp(a.len() == 3);
	}
}

#endif /* Include guard */
