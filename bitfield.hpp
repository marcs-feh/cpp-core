// A Bitfield is a linear collection of bits stored in a big-endian fashion.

#ifndef _bitfield_hpp_include_
#define _bitfield_hpp_include_

// TODO: Shift operations, bitwise ops

#include "types.hpp"
#include "assert.hpp"
#include "mem/allocator.hpp"

template<usize N>
struct Bitfield {
	u8 data[alignForward(N, sizeof(u8)*8) / 8] = {0};

	// Bounds unchecked access
	u8 operator[](usize idx){
		usize byteIdx = (N / 8) - (idx / 8);
		usize bitOff = idx % 8;
		usize bitMask = 1 << bitOff;

		u8 b = (data[byteIdx] & bitMask) != 0;
		return b;
	}

	// Bounds checked access
	u8 get(usize idx){
		panicAssert(idx < N, "Out of bounds access to Bitfield");
		return operator[](idx);
	}

	// Set bit at position idx to v
	void set(usize idx, u8 v){
		usize byteIdx = (N / 8) - (idx / 8);
		usize bitOff = idx % 8;
		u8 b = (v != 0);

		data[byteIdx] &= ~(1 << bitOff);
		data[byteIdx] |= (b << bitOff);
	}

	Bitfield() = default;
};


#endif /* Include guard */
