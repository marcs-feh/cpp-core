#ifndef _bump_allocator_hpp_include_
#define _bump_allocator_hpp_include_

#include "allocator.hpp"
#include "slice.hpp"

// TODO: Check if allocator owns dealloc'd pointer! return false if it doesnt

struct BumpAllocator : Allocator {
	usize off = 0;
	usize cap = 0;
	void* buf = nullptr;

	void* alloc(usize n) override;
	bool  dealloc(void* ptr) override;
	bool  deallocAll() override;
	void* allocUndef(usize n) override;

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
	bool destroy(T* ptr){
		if(ptr == nullptr){ return true; }
		ptr->~T();
		return true;
	}

	// TODO: ownership check
	template<typename T>
	bool destroy(Slice<T>& s){
		if(!s){ return true; }
		usize n = s.len();
		for(usize i = 0; i < n; i += 1){
			s[i].~T();
		}
		dealloc(s.ptr());
		s = Slice<T>(); // Clear slice
		return true;
	}

	~BumpAllocator();
};
#endif /* Include guard */
