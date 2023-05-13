#include "test/test.hpp"

// Tests
#include "_tests/bump_allocator.cpp"
#include "_tests/dummy.cpp"
#include "_tests/maybe.cpp"
#include "_tests/result.cpp"
#include "_tests/defer.cpp"
#include "_tests/bitfield.cpp"
#include "_tests/slice.cpp"

int main() {
	test_bumpAllocator();
	test_maybe();
	test_result();
	test_defer();
	test_bitfield();
	test_slice();
	return 0;
}

