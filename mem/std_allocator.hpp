#ifndef _std_allocator_hpp_include_
#define _std_allocator_hpp_include_

#include "mem/allocator.hpp"
#include <cstdlib>

// TODO: ownership system
namespace core {
struct StdAllocator : Allocator {
	void* alloc(usize n) override {
		void* p = std::malloc(n);
		if(p != nullptr){ mem_zero(p, n); }
		return p;
	}

	void dealloc(void* ptr) override {
		if(ptr == nullptr){ return; };
		std::free(ptr);
	}

	void dealloc_all() override { return; }

	void* alloc_undef(usize n) override {
		return std::malloc(n);
	}

	constexpr
	u8 capabilities() override {
		return can_alloc_any | can_dealloc_one | can_grow;
	}

	StdAllocator() = default;
	StdAllocator(const StdAllocator& s) = default;
	StdAllocator& operator=(const StdAllocator& s) = default;
	StdAllocator(StdAllocator&& s) = default;
	StdAllocator& operator=(StdAllocator&& s) = default;
	~StdAllocator() = default;
};
}

#endif /* Include guard */
