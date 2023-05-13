#include "mem/bump_allocator.hpp"
#include "test/test.hpp"

#include "dummy.cpp"

void test_bumpAllocator(){
	Test T("Bump Allocator");
	constexpr usize n = 64;
	void* buf = new byte[n];

	BumpAllocator al(buf, n);
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

	Tp(!al.dealloc(nums));
	Tp(al.alloc(20) == nullptr);
	Tp(al.alloc(3) != nullptr);

	Tp(al.dealloc_all());
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

	delete [] (byte*)buf;
}

