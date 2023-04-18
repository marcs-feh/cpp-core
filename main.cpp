#define ASSERT_ENABLE 1
#include "test/test.hpp"
#include "assert.hpp"
#include "mem/allocator.hpp"
#include "mem/bump_allocator.hpp"

// Tests
#include "_tests/bump_allocator.cpp"

int main(){
	test::bumpAllocator();
	return 0;
}

