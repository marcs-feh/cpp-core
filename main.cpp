#define ASSERT_ENABLE 1
#include "test/test.hpp"
#include "assert.hpp"
// #include "mem/allocator.hpp"
// #include "mem/bump_allocator.hpp"
#include "defer.hpp"

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
	return 0;
}

