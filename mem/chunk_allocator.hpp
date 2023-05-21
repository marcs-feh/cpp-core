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

	usize free_chunk_count() const;

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

	// Allocate a specific type and run its constructor with args in-place, returns nullptr if failed.
	template<typename T, typename... Args>
	Slice<T> makeSlice(usize n, Args ...ctorArgs){
		if(n == 0){ return Slice<T>(); }

		T* p = (T*)alloc(sizeof(T) * n);
		Slice<T> s = Slice(p, n);

		if(p != nullptr){
			usize n = s.len();
			for(usize i = 0; i < n; i += 1){
				new (s.data + i) T(ctorArgs...);
			}
		}

		return s;
	}


	// De allocates a pointer owned by allocator and runs type's destructor
	template<typename T>
	void destroy(T* ptr){
		if(!ptr){ return; }
		ptr->~T();
		dealloc(ptr);
	}

	template<typename T>
	void destroy(Slice<T>& s){
		if(!s){ return; }
		usize n = s.len();
		for(usize i = 0; i < n; i += 1){
			s[i].~T();
		}
		dealloc(s.ptr());
	}

	static_assert(sizeof(FreeList) == sizeof(Node), "Free list isnt the same size as node, that's a big problem");
};
}
#endif /* Include guard */
