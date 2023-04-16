#ifndef _allocator_hpp_include_
#define _allocator_hpp_include_

#include "types.hpp"

static inline
constexpr bool isPowerOf2(usize n){
	return (n & (n - 1)) == 0;
}

static inline
constexpr uintptr alignForward(uintptr p, uintptr a){
	return 0;
}

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
};

#endif /* Include guard */
