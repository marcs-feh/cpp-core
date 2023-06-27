#ifndef _dyn_array_hpp_include_
#define _dyn_array_hpp_include_

#include "types.hpp"
#include "mem/allocator.hpp"

namespace core {
template<typename T, AllocatorLike A>
struct DynArray {
	usize lenght = 0;
	usize capacity = 0;
	T* data = nullptr;
	A* allocator = nullptr;

	// TODO: function to check for null vec

	constexpr usize cap(){ return capacity; }
	constexpr usize len(){ return lenght; }

	// TODO: use allocator.resize()
	bool resize(usize n){
		if(n < lenght){ return false; }
		T* new_data = static_cast<T*>(allocator->alloc(n * sizeof(T)));

		if(new_data == nullptr){ return false; }

		for(usize i = 0; i < lenght; i += 1){
			new (&new_data[i]) T(move(data[i]));
		}

		allocator->dealloc(data);
		data = new_data;
		capacity = n;
		return true;
	}

	// Append item to list, returns new list lenght or 0 if could not append
	usize append(const T& e){
		if((lenght + 1) >= capacity){
			usize new_cap = (capacity * growth_factor) + 1;
			bool ok = resize(new_cap);
			if(!ok){ return 0; } // ERROR
		}

		new (&data[lenght]) T(e);
		lenght += 1;
		return lenght;
	}

	// Bounds checked access
	T& at(usize idx){
		Panic_Assert((idx < lenght) && (data != nullptr), "Bad access to DynArray");
		return data[idx];
	}

	// Bounds unchecked access when RELEASE_MODE is enabled
	T& operator[](usize idx){
		Assert((idx < lenght) && (data != nullptr), "Bad access to DynArray");
		return data[idx];
	}

	// Bounds checked access (const)
	const T& at(usize idx) const {
		Panic_Assert((idx < lenght) && (data != nullptr), "Bad access to DynArray");
		return data[idx];
	}

	// Bounds unchecked access when RELEASE_MODE is enabled (const)
	const T& operator[](usize idx) const {
		Assert((idx < lenght) && (data != nullptr), "Bad access to DynArray");
		return data[idx];
	}

	DynArray(A* alloc, usize reserve = default_capacity) : capacity(reserve), allocator(alloc){
		if(reserve < min_capacity){ capacity = min_capacity; }
		data = static_cast<T*>(allocator->alloc(sizeof(data) * capacity));
		if(data == nullptr){
			*this = {0};
		}
	}

	DynArray() = delete;
	DynArray(const DynArray& d) = delete;
	DynArray& operator=(const DynArray& d) = delete;

	// TODO: clone()

	~DynArray(){
		if(data){
			allocator->dealloc(data);
			data = nullptr;
		}
	}

	static constexpr usize default_capacity = 16;
	static constexpr usize min_capacity = 4;
	static constexpr f32 growth_factor = 2.0;
};
}

#endif /* Include guard */
