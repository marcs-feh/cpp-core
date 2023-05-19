#ifndef _chunk_allocator_cpp_include_
#define _chunk_allocator_cpp_include_

#include "test/test.hpp"
#include "mem/chunk_allocator.hpp"

using namespace core;

void test_chunkAllocator(){
	Test T("Chunk Allocator");
	constexpr usize n = 200;
	byte* buf = new byte[n];
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
