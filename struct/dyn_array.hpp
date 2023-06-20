#ifndef _dyn_array_hpp_include_
#define _dyn_array_hpp_include_

#include "types.hpp"
#include "mem/allocator.hpp"
#include "mem/default_allocator.hpp"

namespace core {
template<typename T, AllocatorLike A>
struct DynArray {

	usize lenght;
	usize capacity;
	T* data;
	A* allocator;

	DynArray(A* alloc = default_allocator){}
	~DynArray(){}
};
}

#endif /* Include guard */
