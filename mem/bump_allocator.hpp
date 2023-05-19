// A bump allocator is a flat array of memory that has a max capacity and an
// offset. Allocating "bumps" the offset forward, and De-allocating all memory
// is simply resetting the offset

#ifndef _bump_allocator_hpp_include_
#define _bump_allocator_hpp_include_

#include "allocator.hpp"
#include "slice.hpp"

namespace core {

struct BumpAllocator : Allocator {
	usize off = 0;
	usize cap = 0;
	void* buf = nullptr;

	void* alloc(usize n) override;
	void  dealloc(void* ptr) override;
	void  dealloc_all() override;
	void* alloc_undef(usize n) override;

	BumpAllocator() = default;
	BumpAllocator(void* buf, usize bufsize);

	BumpAllocator(BumpAllocator&& al);
	void operator=(BumpAllocator&& al);

	BumpAllocator(const BumpAllocator&) = delete;
	void operator=(const BumpAllocator&) = delete;

	template<typename T, typename... Args>
	T* make(Args ...ctorArgs){
		T* ptr = (T*)alloc(sizeof(T));
		if(ptr == nullptr){ return nullptr; }
		return new (ptr) T(ctorArgs...);
	}

	template<typename T, typename... Args>
	Slice<T> makeSlice(usize n, Args ...ctorArgs){
		T* ptr = (T*)alloc(sizeof(T) * n);
		Slice<T> s(ptr, n);
		if(s){
			for(usize i = 0; i < n; i += 1){
				new (&ptr[i]) T(ctorArgs...);
			}
		}
		return s;
	}

	template<typename T>
	void destroy(T* ptr){
		if(ptr == nullptr){ return; }
		ptr->~T();
	}

	template<typename T>
	void destroy(Slice<T>& s){
		if(!s){ return; }
		usize n = s.len();
		for(usize i = 0; i < n; i += 1){
			s[i].~T();
		}
		dealloc(s.ptr());
		s = Slice<T>(); // Clear slice
	}

	~BumpAllocator();
};
}
#endif /* Include guard */
