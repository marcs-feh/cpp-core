#ifndef _array_hpp_include_
#define _array_hpp_include_

#include "types.hpp"
#include "utils.hpp"
#include "assert.hpp"

namespace core {

template<typename T, usize N>
struct Array {
	T data[N];

	constexpr
	usize len() const { return N; }

	// Bounds unchecked access when RELEASE_MODE is enabled
	T& operator[](usize idx){
		Assert(idx < N, "Out of bounds access");
		return data[idx];
	}

	// Bounds unchecked access when RELEASE_MODE is enabled
	const T& operator[](usize idx) const {
		Assert(idx < N, "Out of bounds access");
		return data[idx];
	}

	// Bounds checked access
	T& at(usize idx){
		Panic_Assert(idx < N, "Out of bounds access");
		return data[idx];
	}

	// Bounds checked access
	const T& at(usize idx) const {
		Panic_Assert(idx < N, "Out of bounds access");
		return data[idx];
	}

	template<typename U>
	T at_or(usize idx, U&& alt){
		if(idx >= N){
			return static_cast<T>(forward<U>(alt));
		}
		return data[idx];
	}

	static_assert(N > 0, "Zero lenght arrays are not allowed");
};

}

#endif /* Include guard */
