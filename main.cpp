#define ASSERT_ENABLE 1
#include "test/test.hpp"
#include "bitfield.hpp"

// Tests
#include "_tests/bump_allocator.cpp"
#include "_tests/dummy.cpp"
#include "_tests/maybe.cpp"
#include "_tests/result.cpp"
#include "_tests/defer.cpp"

int main() {
	test_bumpAllocator();
	test_maybe();
	test_result();
	test_defer();
	constexpr usize n = 16;
	Bitfield<n> bf;
	bf.set(0, 1);
	bf.set(8, 1);
	printf("{ %02x %02x }\n", bf.data[0], bf.data[1]);
	printf("{ ");
	for(ssize i = (n - 1); i >= 0; i -= 1){
		// printf("%td:", i);
		printf("%d ", bf[i]);
		if((i != 0) && (i % 8 == 0)){ printf("| "); }
	}
	printf("}\n");
	bf.set(9, 1);
	bf.set(8, 0);
	printf("{ ");
	for(ssize i = (n - 1); i >= 0; i -= 1){
		// printf("%td:", i);
		printf("%d ", bf[i]);
		if((i != 0) && (i % 8 == 0)){ printf("| "); }
	}
	printf("}\n");
	return 0;
}

