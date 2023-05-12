#ifndef _slice_hpp_include_
#define _slice_hpp_include_

#include "types.hpp"
#include "utils.hpp"
#include "assert.hpp"

template<typename T>
struct Slice {
	usize lenght;
	T* data;

	constexpr usize len() const { return lenght; }
	constexpr T* ptr() const { return data; }

	// Bounds checked access
	T& at(usize idx) & {
		Panic_Assert((idx < lenght) && (data != nullptr), "Bad access to slice");
		return data[idx];
	}

	// Bounds unchecked access when RELEASE_MODE is enabled
	T& operator[](usize idx) & {
		Assert((idx < lenght) && (data != nullptr), "Bad access to slice");
		return data[idx];
	}

	// Get element at position, if out of bounds or slice's data is null, return alt
	template<typename U>
	T atOr(usize idx, U&& alt) const {
		if((idx >= lenght) || (data == nullptr)){
			return static_cast<T>(forward<U>(alt));
		}
		return data[idx];
	}

	// Bounds and null checked access (const)
	const T& at(usize idx) const& {
		Panic_Assert((idx < lenght) && (data != nullptr), "Bad access to slice");
		return data[idx];
	}

	// Unchecked access when RELEASE_MODE is enabled (const)
	const T& operator[](usize idx) const& {
		Assert((idx < lenght) && (data != nullptr), "Bad access to slice");
		return data[idx];
	}

	// Creates a new slice from a to b (end-exclusive), returns a null slice on bad range
	Slice slice(usize from, usize upto){
		bool badRange = (from >= lenght) || (upto >= lenght) || (from > upto);
		if(badRange){ return Slice(nullptr, 0); }

		return Slice(data + from, upto - from);
	}

	// 2 slices are equal if they have the same size and their elements are equal
	bool eq(const Slice& s) const {
		if(s.lenght != lenght){ return false; }
		for(usize i = 0; i < lenght; i += 1){
			if(s[i] != data[i]){ return false; }
		}
		return true;
	}

	Slice() : data{0}, lenght{0} {}

	Slice(T* p, usize l) : data(p), lenght(l) {}

	Slice(const Slice& s) : data(s.data), lenght(s.lenght) {}

	Slice(Slice&& s) : data(s.data), lenght(s.lenght) {
		s.data = nullptr;
		s.lenght = 0;
	}

	void operator=(const Slice&& s){
		data = s.data;
		lenght = s.lenght;
	}

	void operator=(Slice&& s){
		data = s.data;
		lenght = s.lenght;
		s.lenght = 0;
		s.data = nullptr;
	}

	~Slice() = default;
};

#endif /* Include guard */
