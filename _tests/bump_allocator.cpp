#include "mem/linear_allocator.cpp"
#include "test/test.hpp"
using namespace core;

#include "dummy.cpp"

void test_linearAllocator(){
	Test T("Linear Allocator");
	constexpr usize n = 64;
	void* buf = new byte[n];

	LinearAllocator al(buf, n);
	Tp(al.buf != nullptr);
	Tp(al.cap == n);
	Tp(al.off == 0);
	i32* nums = (i32*)al.alloc(sizeof(*nums) * 10);
	Tp(nums != nullptr);

	bool zeroed = true;
	for(usize i = 0; i < 10; i += 1){
		if(nums[i] != 0){ zeroed = false; }
	}
	Tp(zeroed);

	al.dealloc(nums);
	Tp(al.alloc(20) == nullptr);
	Tp(al.alloc(3) != nullptr);

	al.dealloc_all();
	Tp(al.cap == n);
	Tp(al.off == 0);

	{
		A::reset();
		A *e = al.make<A>();
		Tp(A::ctorUses == 1);
		al.destroy(e);
		Tp(A::dtorUses == 1);
	}
	al.dealloc_all();
	{
		A::reset();
		constexpr uint aCount = 5;
		auto aa = al.makeSlice<A>(aCount);
		Tp(A::ctorUses == aCount);
		al.destroy(aa);
		Tp(A::dtorUses == aCount);
	}

	{
		LinearAllocator al0(buf, 20);
		Tp(al0.buf == buf);
		Tp(al0.cap == 20);
		LinearAllocator al1 = move(al0);
		Tp(al0.buf == nullptr);
		Tp(al0.cap == 0);
		Tp(al1.buf == buf);
		Tp(al1.cap == 20);

	}

	delete [] (byte*)buf;
}

