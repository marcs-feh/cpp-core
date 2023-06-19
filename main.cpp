#include "test/test.hpp"

// Tests
#include "_tests/bump_allocator.cpp"
#include "_tests/chunk_allocator.cpp"
#include "_tests/dummy.cpp"
#include "_tests/maybe.cpp"
#include "_tests/result.cpp"
#include "_tests/defer.cpp"
#include "_tests/bitfield.cpp"
#include "_tests/slice.cpp"
#include "_tests/complex.cpp"
#include "_tests/array.cpp"
#include "_tests/static_list.cpp"
#include "_tests/static_stack.cpp"

#include "struct/dyn_array.hpp"
#include "error.hpp"

int main() {
	test_linearAllocator();
	test_chunkAllocator();
	test_maybe();
	test_result();
	test_defer();
	test_bitfield();
	test_slice();
	test_complex();
	test_array();
	test_staticList();
	test_staticStack();
	return 0;
}

