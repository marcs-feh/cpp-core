#ifndef _dyn_array_hpp_include_
#define _dyn_array_hpp_include_

#include "types.hpp"
#include "mem/allocator.hpp"

namespace core {
template<typename T, typename Allocator>
struct DynArray {
	usize lenght;
	usize capacity;
	T* data;

	DynArray() : lenght{0}, capacity{0} {
	}

	~DynArray(){
	}
};
}

#endif /* Include guard */
