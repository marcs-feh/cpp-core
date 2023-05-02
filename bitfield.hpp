// A Bitfield is a linear collection of bits stored in a big-endian fashion.

#ifndef _bitfield_hpp_include_
#define _bitfield_hpp_include_

// TODO: Shift operations, bitwise ops
#include <initializer_list>

#include "utils.hpp"
#include "types.hpp"
#include "assert.hpp"
#include "mem/allocator.hpp"

template<usize N>
struct Bitfield {
	u8 data[alignForward(N, sizeof(u8)*8) / 8] = {0};

	constexpr
	usize len() const {
		return N;
	}

	constexpr
	usize cap() const {
		return alignForward(N, sizeof(u8)*8) / 8;
	}

	// Bounds unchecked access
	u8 operator[](usize idx) const {
		usize byteIdx = (N / 8) - (idx / 8);
		usize bitOff = idx % 8;
		usize bitMask = 1 << bitOff;

		u8 b = (data[byteIdx] & bitMask) != 0;
		return b;
	}

	// Bounds checked access
	u8 get(usize idx) const {
		panicAssert(idx < N, "Out of bounds access to Bitfield");
		return operator[](idx);
	}

	// Set bit at position idx to v
	void set(usize idx, u8 v){
		if(idx >= N){ return; }
		usize byteIdx = (N / 8) - (idx / 8);
		usize bitOff = idx % 8;
		u8 b = (v != 0);

		data[byteIdx] &= ~(1 << bitOff);
		data[byteIdx] |= (b << bitOff);
	}

	// Flip bit at position idx
	void flip(usize idx){
		if(idx >= N){ return; }
		u8 b = operator[](idx);
		set(idx, !b);
	}

	Bitfield operator|(const Bitfield& bf){
		Bitfield<N> res;
		for(usize i = 0; i < cap(); i += 1){
			res.data[i] = bf.data[i] | data[i];
		}
		return res;
	}

	Bitfield operator~(){
		Bitfield<N> res;
		for(usize i = 0; i < cap(); i += 1){
			res.data[i] = ~data[i];
		}
		return res;
	}

	Bitfield operator&(const Bitfield& bf){
		Bitfield<N> res;
		for(usize i = 0; i < cap(); i += 1){
			res.data[i] = bf.data[i] & data[i];
		}
		return res;
	}

	Bitfield operator^(const Bitfield& bf){
		Bitfield<N> res;
		for(usize i = 0; i < cap(); i += 1){
			res.data[i] = bf.data[i] ^ data[i];
		}
		return res;
	}

	bool operator==(const Bitfield &bf) {
		for(usize i = cap() - 1; i > 0; i -= 1){
			if(bf.data[i] != data[i]){ return false; }
		}
		// Last byte is checked on a bit by bit basis to ensure padding bits
		// don't change result
		usize off = (cap() * 8) - len();
		u8 b1 = data[0] << off;
		u8 b0 = bf.data[0] << off;
		return b0 == b1;
	}

	Bitfield() = default;

	Bitfield(const Bitfield& bf){
		for(usize i = 0; i < cap(); i += 1){
			data[i] = bf.data[i];
		}
	}

	template<typename T>
	Bitfield(const std::initializer_list<T>& l) : data{0}{
		usize i = min(len(), l.size());
		for(const auto& e : l){
			i -= 1;
			set(i, bool(e));
			if(i == 0){ break; }
		}
	}

	void operator=(const Bitfield& bf){
		for(usize i = 0; i < cap(); i += 1){
			data[i] = bf.data[i];
		}
	}

	template<typename T>
	void operator=(const std::initializer_list<T>& l){
		usize i = min(len(), l.size());
		for(const auto& e : l){
			i -= 1;
			set(i, bool(e));
			if(i == 0){ break; }
		}
	}

	static_assert(N > 0, "Bitfield must be at least 1 wide");
};


#endif /* Include guard */
