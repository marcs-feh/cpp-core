// A Slice is a very lightweight wrapper around pointers, it adds optional
// bounds checking and size information, a Slice does not own its pointer and
// will never free it.

#ifndef _slice_hpp_include_
#define _slice_hpp_include_

#include "types.hpp"
#include "utils.hpp"
#include "assert.hpp"

namespace core {

template<typename T>
struct Slice {
	usize lenght = 0;
	T* data = nullptr;

	constexpr
	usize len() const { return lenght; }

	constexpr
	T* ptr() const { return data; }

	// A slice is considered null if its pointer is nullptr or its lenght is 0
	constexpr
	bool null() const {
		return (data == nullptr) || (lenght == 0);
	}

	constexpr operator bool(){ return !null(); }

	// Bounds checked access
	T& at(usize idx) {
		Panic_Assert((idx < lenght) && (data != nullptr), "Bad access to slice");
		return data[idx];
	}

	// Bounds unchecked access when RELEASE_MODE is enabled
	T& operator[](usize idx) {
		Assert((idx < lenght) && (data != nullptr), "Bad access to slice");
		return data[idx];
	}

	// Get element at position, if out of bounds or slice's data is null, return alt
	template<typename U>
	T at_or(usize idx, U&& alt) const {
		if((idx >= lenght) || (data == nullptr)){
			return static_cast<T>(forward<U>(alt));
		}
		return data[idx];
	}

	// Bounds and null checked access (const)
	const T& at(usize idx) const {
		Panic_Assert((idx < lenght) && (data != nullptr), "Bad access to slice");
		return data[idx];
	}

	// Unchecked access when RELEASE_MODE is enabled (const)
	const T& operator[](usize idx) const {
		Assert((idx < lenght) && (data != nullptr), "Bad access to slice");
		return data[idx];
	}

	// Creates a new slice from a to b (end-exclusive), returns a null slice on bad range
	Slice slice(usize from, usize upto){
		bool badRange = (from >= lenght) || (upto >= lenght) || (from > upto);
		if(badRange){ return Slice(nullptr, 0); }

		return Slice(data + from, upto - from);
	}

	Slice(){}

	Slice(T* p, usize l) : lenght(l), data(p) {}

	Slice(const Slice& s) : lenght(s.lenght), data(s.data) {}

	Slice(Slice&& s) : lenght(s.lenght), data(s.data) {
		s.data   = nullptr;
		s.lenght = 0;
	}

	void operator=(const Slice& s){
		data   = s.data;
		lenght = s.lenght;
	}

	void operator=(Slice&& s){
		data   = exchange(s.data, nullptr);
		lenght = exchange(s.lenght, 0);
	}

	~Slice() = default;
};

// 2 slices are equal if they have the same size and their elements are equal
template<typename T>
constexpr
bool operator==(const Slice<T>& l, const Slice<T>& r){
	if(l.lenght != r.lenght){ return false; }
	for(usize i = 0; i < l.len(); i += 1){
		if(l.data[i] != r.data[i]){ return false; }
	}
	return true;
}
}
#endif /* Include guard */
