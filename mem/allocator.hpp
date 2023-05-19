#ifndef _allocator_hpp_include_
#define _allocator_hpp_include_

#include "types.hpp"
#include "assert.hpp"
#include "utils.hpp"
#include <cstddef>
namespace core {

// TODO: Stop using virtual for Allocator
// TODO: Check if allocator owns dealloc'd pointer! return false if it doesnt

// This function may take any unsigned integer type.
template<typename T>
static constexpr
bool is_pow_of_2(T n){
	return (n & (n - 1)) == 0;
}

// Check if pointer is within 2 other addresses (inclusive), if `from` is bigger
// than `to` this always returns false
static constexpr
bool ptr_in_range(uintptr from, uintptr p, uintptr to){
	return (p >= from) && (p <= to);
}

// Align a value to a specific alignment `a`. This function may take any
// unsigned integer type.
template<typename T>
constexpr
T align_forward(T p, T a){
	T mod = p % a;

	if(mod > 0){
		p += (a - mod);
	}

	return p;
}

// Memory allocator interface
struct Allocator {
	// Allocate n bytes, all initialized to 0, returns nullptr if allocation failed
	virtual void* alloc(usize n) = 0;
	// Free a pointer. Freeing nullptr doesnt do anything.
	virtual void dealloc(void* ptr) = 0;
	// Free all pointers owned by allocator.
	virtual void dealloc_all() = 0;
	// Allocate n uninitialized bytes, returns nullptr if allocation failed
	virtual void* alloc_undef(usize n) = 0;
	// Allocate a specific type and run its constructor with args in-place, returns nullptr if failed.
	template<typename T, typename... Args>
	T* make(Args ...ctorArgs);
	// De allocates a pointer owned by allocator and runs type's destructor, returns success status
	template<typename T>
	bool destroy(T* ptr);
	// Default alignment choice
	static constexpr usize defAlign = alignof(max_align_t);
};

}

#endif /* Include guard */
