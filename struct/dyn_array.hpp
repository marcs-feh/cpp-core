#ifndef _dyn_array_hpp_include_
#define _dyn_array_hpp_include_

#include "types.hpp"
#include "mem/allocator.hpp"

namespace core {
template<typename T, Allocator auto alloc>
struct DynArray {
	usize lenght;
	usize capacity;
	T* data;

	~DynArray(){}
};
}

#endif /* Include guard */
