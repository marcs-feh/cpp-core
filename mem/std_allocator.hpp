#ifndef _std_allocator_hpp_include_
#define _std_allocator_hpp_include_

#include "mem/allocator.hpp"
#include <cstdlib>

// TODO: ownership system
namespace core {
struct LibcAllocator : Allocator {
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
		return can_alloc_any | can_dealloc_one | dynamic_cap;
	}

	LibcAllocator() = default;
	LibcAllocator(const LibcAllocator& s) = default;
	LibcAllocator& operator=(const LibcAllocator& s) = default;
	LibcAllocator(LibcAllocator&& s) = default;
	LibcAllocator& operator=(LibcAllocator&& s) = default;
	~LibcAllocator() = default;
};
}

#endif /* Include guard */
