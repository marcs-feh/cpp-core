#include "bump_allocator.hpp"

using A = BumpAllocator;

A::BumpAllocator(void* buffer, usize bufsize) : off{0}, cap{0} {
	if(buffer == nullptr){
		return;
	}
	buf = buffer;
	cap = bufsize;
}

void* A::allocUndef(usize n){
	uintptr buf = (uintptr)this->buf;
	uintptr base = (buf + off);
	uintptr pad = alignForward(base, defAlign) - base;

	// No memory left.
	if((base + pad + n) >= (buf + cap)){
		return nullptr;
	}

	void* ptr = (void*)(base + pad);
	off += n + pad;

	return ptr;
}

void* A::alloc(usize n){
	byte* p = (byte*)allocUndef(n);
	if(p != nullptr){
		// TODO: Vectorize? Or at least fill using word-sized integers.
		for(usize i = 0; i < n; i += 1){
			p[i] = 0;
		}
	}
	return (void*)p;
}

// BumpAllocator does not support individual free
bool A::free(void*){
	return false;
}

bool A::freeAll(){
	off = 0;
	return true;
}

A::BumpAllocator(BumpAllocator&& al) : off{al.off}, cap{al.cap}, buf{al.buf} {
	al.buf = nullptr;
	al.cap = 0;
	al.off = 0;
}

void A::operator=(BumpAllocator&& al){
	al.buf = nullptr;
	al.cap = 0;
	al.off = 0;
}

A::~BumpAllocator(){}

