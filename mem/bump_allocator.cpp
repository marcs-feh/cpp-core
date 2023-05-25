#include "bump_allocator.hpp"

using A = core::BumpAllocator;

A::BumpAllocator(void* buffer, usize bufsize) : off{0}, cap{0} {
	if(buffer == nullptr){
		return;
	}
	buf = buffer;
	cap = bufsize;
}

void* A::alloc_undef(usize n) {
	uintptr buf = (uintptr)this->buf;
	uintptr base = (buf + off);
	uintptr pad = align_forward(base, defAlign) - base;

	// No memory left.
	if((base + pad + n) > (buf + cap)){
		return nullptr;
	}

	void* ptr = (void*)(base + pad);
	off += n + pad;

	return ptr;
}

void* A::alloc(usize n) {
	byte* p = (byte*)alloc_undef(n);
	if(p != nullptr){
		mem_zero(p, n);
	}
	return (void*)p;
}

// BumpAllocator does not support individual dealloc
void A::dealloc(void*){
	return;
}

void A::dealloc_all() {
	off = 0;
}

A::BumpAllocator(BumpAllocator &&al) : off{al.off}, cap{al.cap}, buf{al.buf} {
	al.buf = nullptr;
	al.cap = 0;
	al.off = 0;
}

void A::operator=(BumpAllocator&& al) {
	al.buf = nullptr;
	al.cap = 0;
	al.off = 0;
}

A::~BumpAllocator(){}

