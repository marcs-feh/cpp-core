#ifndef _chunk_allocator_hpp_include_
#define _chunk_allocator_hpp_include_

#include "allocator.hpp"

namespace core {
struct ChunkAllocator : Allocator {
	struct Node {
		Node* next = nullptr;
	};

	struct FreeList {
		Node* head = nullptr;
		void add(Node* node);
		Node* pop();
	};

	usize chunk_size  = sizeof(FreeList);
	usize chunk_count = 0;
	usize buf_size    = 0;
	void* data        = nullptr; 
	FreeList free_list;

	void* alloc(usize n) override;
	void  dealloc(void* ptr) override;
	void  dealloc_all() override;
	void* alloc_undef(usize n) override;

	ChunkAllocator() = default;
	ChunkAllocator(void* buf, usize bufsize, usize chunk_size, usize chunk_count);

	// Allocate a specific type and run its constructor with args in-place, returns nullptr if failed.
	template<typename T, typename... Args>
	T* make(Args ...ctorArgs){
		T* p = (T*)alloc(sizeof(T));
		if(p != nullptr){
			new (p) T(ctorArgs...);
		}
		return p;
	}

	// De allocates a pointer owned by allocator and runs type's destructor
	template<typename T>
	void destroy(T* ptr){
		if(!ptr){ return; }
		ptr->~T();
		dealloc(ptr);
	}

	static_assert(sizeof(FreeList) == sizeof(Node), "Free list isnt the same size as node, that's a big problem");
};
}
#endif /* Include guard */
