// This arena allocator is essentially a LinearAllocator with dynamic storage.
// This allocator can grow its capacity.

#ifndef _arena_allocator_cpp_include_
#define _arena_allocator_cpp_include_

#include "mem/allocator.hpp"
#include "mem/linear_allocator.cpp"
#include "defer.hpp"

namespace core {
template<AllocatorLike Al>
struct ArenaAllocator {
	struct Block {
		LinearAllocator allocator;
		Block* next = nullptr;

		Block(){}
		Block(LinearAllocator al, Block* next) : allocator(move(al)), next(next) {}
	};

	Block* head = nullptr;
	Al* allocator = nullptr;

	constexpr
	u8 capabilities(){
		return can_alloc_any | can_dealloc_all | dynamic_cap;
	}

	bool append_block(usize nbytes){
		byte* buf = nullptr;
		Block* blk = nullptr;

		buf = allocator->alloc(nbytes);
		if(buf == nullptr){ goto error_exit; }

		blk = make<Block>(allocator, buf, nbytes);
		if(blk == nullptr){ goto error_exit; }

		blk->next = head;
		head = blk;

		return true;

	error_exit:
		allocator->dealloc(buf);
		allocator->dealloc(blk);
		return false;
	}

	void* alloc_undef(usize n){
		void* p = head->allocator.alloc_undef(n);
		if(!p){
			bool ok = append_block(align_forward(usize(n * 1.5), default_align));
			if(!ok){ return nullptr; }
			p = head->allocator.alloc_undef(n);
		}
		return p;
	}

	void* alloc(usize n){

	}

	// Does not support individual dealloc
	void dealloc(void*){
		return;
	}

	// TODO: delete?
	ArenaAllocator(){}


};
}



#endif /* Include guard */
