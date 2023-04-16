#ifndef _allocator_hpp_include_
#define _allocator_hpp_include_

#include "types.hpp"

// Memory allocator interface
struct Allocator {
	// Allocate n bytes, all initialized to 0, returns nullptr if allocation failed
	virtual void* alloc(usize n) = 0;
	// Free a pointer, returns success status
	virtual bool free(void* ptr) = 0;
	// Free all pointers owned by allocator, returns success status
	virtual bool freeAll() = 0;
	// Allocate n uninitialized bytes, returns nullptr if allocation failed
	virtual void* allocUndef(usize n) = 0;
	// Allocate a specific type and run its constructor with args in-place, returns nullptr if failed.
	template<typename T, typename... Args>
	T* make(Args ...ctorArgs);
	// Allocate N units of a specific type and run its constructor with args in-place, returns nullptr if failed.
	template<typename T, usize N, typename... Args>
	T* make(Args ...ctorArgs);
	// De allocates a pointer owned by allocator and runs type's destructor, returns success status
	template<typename T>
	bool destroy(T* ptr);
};

#endif /* Include guard */
