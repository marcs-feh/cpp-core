#ifndef _allocator_hpp_include_
#define _allocator_hpp_include_

#include "types.hpp"
#include "assert.hpp"

#include <cstddef>

// This function may take any unsigned integer type.
template<typename T>
constexpr bool isPowerOf2(T n){
	return (n & (n - 1)) == 0;
}

// Align a value to a specific alignment `a`. This function may take any
// unsigned integer type.
template<typename T>
constexpr T alignForward(T p, T a){
	Assert(isPowerOf2(a), "Alignment must be a power of 2");
	// Same as mod = p % a but only for powers of 2
	T mod = p & (a - 1);

	if(mod > 0){
		p += (a - mod);
	}

	return p;
}

// Needed so the compiler doesnt cry about it
void* operator new(usize, void*) noexcept;

// Memory allocator interface
struct Allocator {
	// Allocate n bytes, all initialized to 0, returns nullptr if allocation failed
	virtual void* alloc(usize n) = 0;
	// Free a pointer, returns success status. free(nullptr) is always true
	virtual bool free(void* ptr) = 0;
	// Free all pointers owned by allocator, returns success status
	virtual bool freeAll() = 0;
	// Allocate n uninitialized bytes, returns nullptr if allocation failed
	virtual void* allocUndef(usize n) = 0;
	// Allocate a specific type and run its constructor with args in-place, returns nullptr if failed.
	template<typename T, typename... Args>
	T* make(Args ...ctorArgs);
	// De allocates a pointer owned by allocator and runs type's destructor, returns success status
	template<typename T>
	bool destroy(T* ptr);
	// Default alignment choice
	static constexpr usize defAlign = alignof(max_align_t);
};

#endif /* Include guard */
