#ifndef _chunk_allocator_cpp_include_
#define _chunk_allocator_cpp_include_

#include "test/test.hpp"
#include "mem/chunk_allocator.hpp"
#include "defer.hpp"

#include "dummy.cpp"

using namespace core;

void test_chunkAllocator(){
	Test T("Chunk Allocator");
	constexpr usize n = 200;
	constexpr usize ch_num = 5;
	byte* buf = new byte[n];
	Defer { delete[] buf; };

	auto al = ChunkAllocator(buf, n, 30, ch_num);
	Tp(al.data);
	Tp(al.chunk_size == align_forward(usize(30), Allocator::defAlign));
	Tp(al.chunk_count == ch_num);

	{
		int before = al.free_chunk_count();
		Tp(al.alloc(5000) == nullptr);
		int after = al.free_chunk_count();
		Tp(before == after);

		void* p = al.alloc(sizeof(i32) * 4);
		Tp(p != nullptr);
		after = al.free_chunk_count();
		Tp(before == (after + 1));
		al.dealloc(p);
		after = al.free_chunk_count();
		Tp(before == after);

		void* ptrs[ch_num];
		bool distinct = true;
		for(usize i = 0; i < ch_num; i += 1){
			ptrs[i] = al.alloc(1);
		}
		for(usize i = 0; i < ch_num; i += 1){
			for(usize j = 0; j < ch_num; j += 1){
				bool same = (ptrs[i] == ptrs[j]) && (i != j);
				if(same){
					distinct = false;
				}
			}
		}
		Tp(al.alloc(1) == nullptr);
		Tp(al.free_chunk_count() == 0);
		Tp(distinct);
		al.dealloc_all();
		Tp(al.free_chunk_count() == ch_num);
	}

	{
		A::reset();
		al.dealloc_all();
		A* ap = al.make<A>();
		Tp(ap != nullptr);
		Tp(A::ctorUses == 1);
		al.destroy(ap);
		Tp(A::dtorUses == 1);
	}
	{
		al.dealloc_all();
		A::reset();
		auto as = al.makeSlice<A>(4);
		Tp(as);
		Tp(A::ctorUses == 4);
		al.destroy(as);
		Tp(A::dtorUses == 4);
	}

	al.dealloc_all();
	{
		{
			auto toomuch   = ChunkAllocator(buf, n, 10, 80);
			auto toolittle = ChunkAllocator(buf, n, 100, 0);
			auto justright = ChunkAllocator(buf, n, 10, 10);
			Tp(toomuch.data == nullptr);
			Tp(toolittle.data == nullptr);
			Tp(justright.data != nullptr);
		}
		{
			auto toomuch   = ChunkAllocator(buf, n, 100, 2);
			auto toolittle = ChunkAllocator(buf, n, 0, 23);
			Tp(toomuch.data == nullptr);
			Tp(toolittle.data == nullptr);
		}
	}

}



#endif /* Include guard */
