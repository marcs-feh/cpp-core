// A linear allocator is a flat array of memory that has a max capacity and an
// offset. Allocating pushes the offset forward, and De-allocating all memory
// is simply resetting the offset

#include "allocator.hpp"
#include "slice.hpp"

namespace core {
struct LinearAllocator {
	usize off = 0;
	usize cap = 0;
	void* buf = nullptr;

	constexpr
	u8 capabilities(){
		return can_alloc_any | can_dealloc_all;
	}

	void* alloc_undef(usize n){
		uintptr buf = (uintptr)this->buf;
		uintptr base = (buf + off);
		uintptr pad = align_forward(base, default_align) - base;

		// No memory left.
		if((base + pad + n) > (buf + cap)){
			return nullptr;
		}

		void* ptr = (void*)(base + pad);
		off += n + pad;

		return ptr;
	}

	void* alloc(usize n){
		byte* p = (byte*)alloc_undef(n);
		if(p != nullptr){
			mem_zero(p, n);
		}
		return (void*)p;
	}

	// Does not support individual dealloc
	void dealloc(void*){
		return;
	}

	void dealloc_all(){
		off = 0;
	}

	LinearAllocator(){};

	LinearAllocator(void* buffer, usize bufsize) : off{0}, cap{0} {
		if(buffer == nullptr){
			return;
		}
		buf = buffer;
		cap = bufsize;
	}

	LinearAllocator(LinearAllocator &&al) : off{al.off}, cap{al.cap}, buf{al.buf} {
		al.buf = nullptr;
		al.cap = 0;
		al.off = 0;
	}

	void operator=(LinearAllocator&& al) {
		buf = exchange(al.buf, nullptr);
		cap = exchange(al.cap, 0);
		off = exchange(al.off, 0);
	}

	LinearAllocator(const LinearAllocator&) = delete;
	void operator=(const LinearAllocator&) = delete;

	~LinearAllocator(){}
};
}
