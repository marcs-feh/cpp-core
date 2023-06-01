#ifndef _chunk_allocator_cpp_include_
#define _chunk_allocator_cpp_include_

#include "allocator.hpp"

namespace core {
struct ChunkAllocator : Allocator {
	struct Node {
		Node* next = nullptr;
	};

	struct FreeList {
		Node* head = nullptr;
		void add(Node* node){
			node->next = head;
			head = node;
		}

		Node* pop(){
			if(head == nullptr){ return nullptr; }
			Node* node = head;
			head = head->next;
			return node;
		}
	};

	usize chunk_size  = sizeof(FreeList);
	usize chunk_count = 0;
	usize buf_size    = 0;
	void* data        = nullptr;
	FreeList free_list;

	constexpr
	u8 capabilities() override {
		return can_dealloc_one | can_dealloc_all;
	}

	usize free_chunk_count() const {
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
	void* alloc(usize n) override {
		void* p = alloc_undef(n);
		if(p != nullptr){
			mem_zero(p, n);
		}
		return p;
	}

	void dealloc(void* ptr) override {
		Node* node = (Node*)ptr;
		free_list.add(node);
	}

	void dealloc_all() override {
		byte* ptr = (byte*)data;
		for(uintptr i = 0; i < chunk_count; i += 1){
			free_list.add((Node*)(&ptr[i * chunk_size]));
		}
	}

	void* alloc_undef(usize n) override {
		if((n > chunk_size) || (free_list.head == nullptr)){
			return nullptr;
		}
		return free_list.pop();
	}

	ChunkAllocator() = default;

	ChunkAllocator(void* buf, usize bufsize, usize chunk_sz, usize chunk_n)
	: free_list() {
		uintptr unaligned = (uintptr)buf;
		uintptr aligned   = align_forward(unaligned, defAlign);
		uintptr shift     = aligned - unaligned;

		usize true_bufsize   = bufsize - shift;
		usize true_chunksize = align_forward(chunk_sz, defAlign);
		usize min_required   = sizeof(FreeList) * chunk_n;
		usize will_need      = max(true_chunksize * chunk_n, min_required);

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

	ChunkAllocator(ChunkAllocator&& c)
		: chunk_size(c.chunk_size), chunk_count(c.chunk_count),
		buf_size(c.buf_size), data(c.data), free_list(c.free_list)
	{
		c.chunk_size  = sizeof(FreeList);
		c.chunk_count = 0;
		c.buf_size    = 0;
		c.data        = nullptr;
		c.free_list   = FreeList();
	}

	ChunkAllocator& operator=(ChunkAllocator&& c){
		chunk_size  = exchange(c.chunk_size, sizeof(FreeList));
		chunk_count = exchange(c.chunk_count, 0);
		buf_size    = exchange(c.buf_size, 0);
		data        = exchange(c.data, nullptr);
		free_list   = exchange(c.free_list, FreeList());
		return *this;
	}

	ChunkAllocator(const ChunkAllocator& c) = delete;
	ChunkAllocator& operator=(const ChunkAllocator& c) = delete;


	~ChunkAllocator(){}

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
