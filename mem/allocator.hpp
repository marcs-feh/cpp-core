#ifndef _allocator_hpp_include_
#define _allocator_hpp_include_

#include "types.hpp"
#include "assert.hpp"
#include "utils.hpp"
#include "slice.hpp"
#include <cstddef>

#if __cplusplus >= 202002L
#include <concepts>
#endif

// TODO: Check if allocator owns dealloc'd pointer! return false if it doesnt
// TODO: Be able to disable concepts
// TODO: Memset impl

namespace core {
// Default memory alignment choice
constexpr usize default_align = alignof(max_align_t);
// Able to alloc memory blocks of any desired size(+align) provided there's enough backing memory
constexpr u8 can_alloc_any = 1 << 0;
// Able to individually dealloc owned pointer
constexpr u8 can_dealloc_one = 1 << 1;
// Able to dealloc all owned pointers
constexpr u8 can_dealloc_all = 1 << 2;
// Able to change capacity (increase or decrease)
constexpr u8 dynamic_cap = 1 << 3;

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

#if __cplusplus >= 202002L
using std::same_as;
using std::convertible_to;

template<typename Impl>
concept AllocatorLike = requires(Impl al, usize n, void* ptr){
// Allocate n bytes, all initialized to 0, returns nullptr if allocation failed
{ al.alloc(n) } -> convertible_to<void*>;
// Free a pointer. Freeing nullptr doesnt do anything.
{ al.dealloc(ptr) } -> same_as<void>;
// Free all pointers owned by allocator.
{ al.dealloc_all() } -> same_as<void>;
// Allocate n uninitialized bytes, returns nullptr if allocation failed
{ al.alloc_undef(n) } -> same_as<void*>;
// Get allocator capabilities
{ al.capabilities() } -> convertible_to<u8>;
};
#else
#define AllocatorLike typename 
#endif

template<typename T, AllocatorLike Alloc, typename... Args>
T* make(Alloc& al, Args&& ...args){
	T* ptr = reinterpret_cast<T*>(al.alloc(sizeof(T)));
	if(ptr){
		new (ptr) T(args...);
	}
	return ptr;
}

// Allocate a specific type and run its constructor with args in-place, returns nullptr if failed.
template<typename T, AllocatorLike Alloc, typename... Args>
Slice<T> make_slice(Alloc& al, usize n, Args ...ctorArgs){
	if(n == 0){ return Slice<T>(); }

	T* p = (T*)al.alloc(sizeof(T) * n);
	auto s = Slice<T>(p, n);

	if(p != nullptr){
		usize n = s.len();
		for(usize i = 0; i < n; i += 1){
			new (s.data + i) T(ctorArgs...);
		}
	}

	return s;
}

// De allocates a pointer owned by allocator and runs type's destructor
template<typename T, AllocatorLike Alloc>
void destroy(Alloc& al, T* ptr){
	if(!ptr){ return; }
	ptr->~T();
	al.dealloc(ptr);
}

template<typename T, AllocatorLike Alloc>
void destroy(Alloc& al, Slice<T>& s){
	if(!s){ return; }
	usize n = s.len();
	for(usize i = 0; i < n; i += 1){
		s[i].~T();
	}
	al.dealloc(s.ptr());
}

}

#endif /* Include guard */
