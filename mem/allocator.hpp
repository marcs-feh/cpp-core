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
constexpr
T alignForward(T p, T a){
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
	// Free a pointer, returns success status. free(nullptr) is always true
	virtual bool dealloc(void* ptr) = 0;
	// Free all pointers owned by allocator, returns success status
	virtual bool deallocAll() = 0;
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
