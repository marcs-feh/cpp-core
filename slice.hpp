#ifndef _slice_hpp_include_
#define _slice_hpp_include_

#include "types.hpp"
#include "utils.hpp"
#include "assert.hpp"

template<typename T>
struct Slice {
	usize lenght;
	T* ptr;

	// Bounds checked access
	T& at(usize idx) & {
		Panic_Assert(idx < lenght, "Out of bounds access");
		return ptr[idx];
	}

	// Bounds unchecked access when RELEASE_MODE is enabled
	T& operator[](usize idx) & {
		Assert(idx < lenght, "Out of bounds access");
		return ptr[idx];
	}

	// Get element at position, if out of bounds or slice's data is null, return alt
	template<typename U>
	T atOr(usize idx, U&& alt) const {
		if((idx >= lenght) || (ptr == nullptr)){
			return static_cast<T>(forward<U>(alt));
		}
		return ptr[idx];
	}

	// Bounds checked access (const)
	const T& at(usize idx) const& {
		Panic_Assert(idx < lenght, "Out of bounds access");
		return ptr[idx];
	}

	// Bounds unchecked access when RELEASE_MODE is enabled (const)
	const T& operator[](usize idx) const& {
		Assert(idx < lenght, "Out of bounds access");
		return ptr[idx];
	}

	// 2 slices are equal if they have the same size and their elements are equal
	bool eq(const Slice& s) const {
		if(s.lenght != lenght){ return false; }
		for(usize i = 0; i < lenght; i += 1){
			if(s[i] != ptr[i]){ return false; }
		}
		return true;
	}

	Slice() : ptr{0}, lenght{0} {}

	Slice(T* p, usize l) : ptr(p), lenght(l) {}

	Slice(const Slice& s) : ptr(s.ptr), lenght(s.lenght) {}

	Slice(Slice&& s) : ptr(s.ptr), lenght(s.lenght) {
		s.ptr = nullptr;
		s.lenght = 0;
	}

	void operator=(const Slice&& s){
		ptr = s.ptr;
		lenght = s.lenght;
	}

	void operator=(Slice&& s){
		ptr = s.ptr;
		lenght = s.lenght;
		s.lenght = 0;
		s.ptr = nullptr;
	}

	~Slice() = default;
};

#endif /* Include guard */
