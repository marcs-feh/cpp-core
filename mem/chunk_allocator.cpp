#include "chunk_allocator.hpp"

using A    = core::ChunkAllocator;
using List = core::ChunkAllocator::FreeList;
using Node = core::ChunkAllocator::Node;

// Bump allocator always allocates the same size, alloc will check if n fits
// into a chunk and if a free chunk is available.
void* A::alloc(usize n){
}

void A::dealloc(void* ptr){
}

void A::dealloc_all(){
	byte* ptr = (byte*)data;
	for(uintptr i = 0; i < chunk_count; i += 1){
		free_list.add((Node*)(&ptr[i * chunk_size]));
	}
}

void* A::alloc_undef(usize n){}

A::ChunkAllocator(void* buf, usize bufsize){
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
