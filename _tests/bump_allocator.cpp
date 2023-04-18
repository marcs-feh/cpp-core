#include "mem/bump_allocator.hpp"
#include "test/test.hpp"

void bumpAllocator(){
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

	Tp(!al.free(nums));
	Tp(al.alloc(20) == nullptr);
	Tp(al.alloc(3) != nullptr);

	Tp(al.freeAll());
	Tp(al.cap == n);
	Tp(al.off == 0);

	delete [] (byte*)buf;
}

