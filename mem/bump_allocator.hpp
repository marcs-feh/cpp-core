#ifndef _bump_allocator_hpp_include_
#define _bump_allocator_hpp_include_

#include "allocator.hpp"

struct BumpAllocator : Allocator {
	void* buf;

	void* alloc(usize n) override;
	bool free(void* ptr) override;
	bool freeAll() override;
	void* allocUndef(usize n) override;

	template<typename T, typename... Args>
	T* make(Args ...ctorArgs){
		void* ptr = alloc(sizeof(T));
		if(ptr == nullptr){ return nullptr; }
		return new (ptr) T(ctorArgs...);
	}

	template<typename T>
	bool destroy(T* ptr){
		if(ptr == nullptr){ return true; }
		ptr->~T();
		return this->free(ptr);
	}
};

#endif /* Include guard */
