#ifndef _chunk_allocator_hpp_include_
#define _chunk_allocator_hpp_include_

#include "allocator.hpp"

struct ChunkAllocator : Allocator {
	struct Node {
		Node* next = nullptr;
	};

	struct FreeList {
		Node* head = nullptr;
		void add(Node* node);
		Node* pop();
	};

	usize chunk_size  = 0;
	usize chunk_count = 0;
	void* data        = nullptr; 
	FreeList free_list;

	void* alloc(usize n) override;
	void  dealloc(void* ptr) override;
	void  dealloc_all() override;
	void* alloc_undef(usize n) override;

	ChunkAllocator() = default;
	ChunkAllocator(void* buf, usize bufsize);

};

#endif /* Include guard */
