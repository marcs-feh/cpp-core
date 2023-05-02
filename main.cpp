#define ASSERT_ENABLE 1
#include "test/test.hpp"
#include "bitfield.hpp"

// Tests
#include "_tests/bump_allocator.cpp"
#include "_tests/dummy.cpp"
#include "_tests/maybe.cpp"
#include "_tests/result.cpp"
#include "_tests/defer.cpp"
#include "_tests/bitfield.cpp"

int main() {
	test_bumpAllocator();
	test_maybe();
	test_result();
	test_defer();
	test_bitfield();
	return 0;
}

