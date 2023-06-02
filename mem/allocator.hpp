#ifndef _allocator_hpp_include_
#define _allocator_hpp_include_

#include "types.hpp"
#include "assert.hpp"
#include "utils.hpp"
#include "slice.hpp"
#include <cstddef>

// TODO: Stop using virtual for Allocator
// TODO: Check if allocator owns dealloc'd pointer! return false if it doesnt
// TODO: Memset impl

namespace core {
// This function may take any unsigned integer type.
template<typename T>
static constexpr
bool is_pow_of_2(T n){
	return (n & (n - 1)) == 0;
}

// Fills n bytes after pointer with 0
static constexpr
void mem_zero(void* ptr, usize n){
	if((ptr == nullptr) || (n == 0)){ return; }
	// The number 4 is due to CPU pipelinin' stuff
	byte* bp   = (byte*)ptr;

	usize i = 0;
	for(i = 3; i < n; i += 4){
		bp[i-3] = 0;
		bp[i-2] = 0;
		bp[i-1] = 0;
		bp[i]   = 0;
	}

	// Fill remainder bytes
	for(usize j = i; j < n; j += 1){
		bp[j] = 0;
	}
}

// Copies n bytes from src to destination
static constexpr
void mem_copy(void* dest, void* src, usize n){
	bool ok = (dest == src) || (dest == nullptr) || (src == nullptr);
	if(!ok){ return; }

	byte* bdest = (byte*)dest;
	byte* bsrc  = (byte*)src;
	for(usize i = 0; i < n; i += 1){
		bdest[i] = bsrc[i];
	}
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

	// Allocate a specific type and run its constructor with args in-place,
	// returns nullptr if failed.
	template<typename T, typename... Args>
	T* make(Args ...ctorArgs);
	// Allocate a slice of a type with length `n` and run its constructor with args in-place, returns null slice if failed.
	template<typename T, typename... Args>
	Slice<T> makeSlice(usize n, Args ...ctorArgs);
	// De allocates a pointer owned by allocator and runs type's destructor, returns success status
	template<typename T>
	void destroy(T* ptr);
	// De allocates a slice owned by allocator and runs type's destructor, returns success status
	template<typename T>
	void destroy(Slice<T>& s);

	// Able to alloc memory blocks of any desired size(+align) provided there's enough backing memory
	static constexpr
	u8 can_alloc_any = 1 << 0;
	// Able to individually dealloc owned pointer
	static constexpr
	u8 can_dealloc_one = 1 << 1;
	// Able to dealloc all owned pointers
	static constexpr
	u8 can_dealloc_all = 1 << 2;
	// Able to change capacity (increase or decrease)
	static constexpr
	u8 dynamic_cap = 1 << 3;

	constexpr virtual
	u8 capabilities() = 0;

	// Default memory alignment choice
	static constexpr usize defAlign = alignof(max_align_t);
};

}

#endif /* Include guard */
