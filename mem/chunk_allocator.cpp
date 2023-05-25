#include "chunk_allocator.hpp"

using A    = core::ChunkAllocator;
using List = core::ChunkAllocator::FreeList;
using Node = core::ChunkAllocator::Node;

usize A::free_chunk_count() const {
	Node* cur = free_list.head;
	if(cur == nullptr){ return 0; }

	usize n;
	for(n = 1; cur->next != nullptr; cur = cur->next){
		n += 1;
	}

	return n;
}

// Bump allocator always allocates the same size, alloc will check if n fits
// into a chunk and if a free chunk is available.
void* A::alloc(usize n){
	void* p = alloc_undef(n);
	if(p != nullptr){
		mem_zero(p, n);
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

// #include <cstdio>
A::ChunkAllocator(void* buf, usize bufsize, usize chunk_sz, usize chunk_n)
: free_list() {
	uintptr unaligned = (uintptr)buf;
	uintptr aligned   = align_forward(unaligned, defAlign);
	uintptr shift     = aligned - unaligned;

	usize true_bufsize   = bufsize - shift;
	usize true_chunksize = align_forward(chunk_sz, defAlign);
	usize min_required   = sizeof(FreeList) * chunk_n;
	usize will_need      = max(true_chunksize * chunk_n, min_required);

	// printf("chunky:\n  wants:%zu\n  bufsize:%zu\n  chunksize:%zu\n", will_need, true_bufsize, true_chunksize);
	bool ok = (true_bufsize >= will_need) &&
		        (chunk_n > 0) && (true_chunksize > 0);
	if(!ok){
		*this = ChunkAllocator();
		return;
	}

	data        = (void*)aligned;
	chunk_size  = true_chunksize;
	buf_size    = true_bufsize;
	chunk_count = chunk_n;

	dealloc_all();
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
