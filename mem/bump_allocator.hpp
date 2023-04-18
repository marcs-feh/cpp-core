#ifndef _bump_allocator_hpp_include_
#define _bump_allocator_hpp_include_

#include "allocator.hpp"

struct BumpAllocator : Allocator {
	usize off = 0;
	usize cap = 0;
	void* buf = nullptr;

	void* alloc(usize n) override;
	bool free(void* ptr) override;
	bool freeAll() override;
	void* allocUndef(usize n) override;

	BumpAllocator() = default;
	BumpAllocator(void* buf, usize bufsize);
	BumpAllocator(BumpAllocator&& al);
	void operator=(BumpAllocator&& al);
	BumpAllocator(const BumpAllocator&) = delete;
	void operator=(const BumpAllocator&) = delete;
	~BumpAllocator();
};

	// template<typename T, typename... Args>
	// T* make(Args ...ctorArgs){
	// 	void* ptr = alloc(sizeof(T));
	// 	if(ptr == nullptr){ return nullptr; }
	// 	return new (ptr) T(ctorArgs...);
	// }
	//
	// template<typename T>
	// bool destroy(T* ptr){
	// 	if(ptr == nullptr){ return true; }
	// 	return false;
	// }
#endif /* Include guard */
