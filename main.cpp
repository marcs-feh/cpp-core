#define ASSERT_ENABLE 1
#include "test/test.hpp"
#include "assert.hpp"
#include "mem/allocator.hpp"

// TODO: alignForward
// TODO: allocator destructor should de-alloc its buffer?

int main(){
	std::printf("%lu\n", alignForward(0x29349, 4));
	std::printf("%lu\n", alignForward(0x29349, 3));
	return 0;
}
