#include "chunk_allocator.hpp"

using A    = core::ChunkAllocator;
using List = core::ChunkAllocator::FreeList;
using Node = core::ChunkAllocator::Node;

// Bump allocator always allocates the same size, alloc will check if n fits
// into a chunk and if a free chunk is available.
void* A::alloc(usize n){
	void* p = alloc_undef(n);
	if(p != nullptr){
		byte* bp = (byte*)p;
		for(usize i = 0; i < n; i += 1){
			bp[i] = 0;
		}
	}
	return p;
}

void A::dealloc(void* ptr){
	Node* node = (Node*)ptr;
	free_list.add(node);
}


void A::dealloc_all(){
	byte* ptr = (byte*)data;
	for(uintptr i = 0; i < chunk_count; i += 1){
		free_list.add((Node*)(&ptr[i * chunk_size]));
	}
}

void* A::alloc_undef(usize n){
	if((n > chunk_size) || (free_list.head == nullptr)){
		return nullptr;
	}
	return free_list.pop();
}

A::ChunkAllocator(void* buf, usize bufsize, usize chunk_sz, usize chunk_n)
: free_list() {
	uintptr unaligned = (uintptr)buf;
	uintptr aligned   = align_forward(unaligned, defAlign);
	uintptr shift     = aligned - unaligned;
	usize actual_size = bufsize - shift;

	bool dontfit = (chunk_sz < sizeof(FreeList)) ||
		             ((chunk_sz * chunk_n) > actual_size) ||
		             (chunk_n == 0);
	if(dontfit){
		*this = ChunkAllocator();
		return;
	}

	data        = (void*)aligned;
	chunk_size  = chunk_sz;
	chunk_count = chunk_n;
	buf_size    = bufsize;

}

void List::add(Node* node){
	node->next = head;
	head = node;
}

Node* List::pop(){
	if(head == nullptr){ return nullptr; }
	Node* node = head;
	head = head->next;
	return node;
}
