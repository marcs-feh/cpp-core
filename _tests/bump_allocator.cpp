#include "mem/bump_allocator.hpp"
#include "test/test.hpp"

namespace test {
void bumpAllocator(){
	Test T("Bump Allocator");
	constexpr usize n = 50;
	void* buf = new byte[n];

	BumpAllocator al(buf, n);
	Tp(al.buf != nullptr);
	Tp(al.cap == 50);
	Tp(al.off == 0);
	i32* nums = (i32*)al.alloc(sizeof(*nums) * 10);
	Tp(nums != nullptr);
	bool zeroed = true;
	for(usize i = 0; i < 10; i += 1){
		if(nums[i] != 0){ zeroed = false; }
	}
	Tp(zeroed);
	delete [] (byte*)buf;
}
}

