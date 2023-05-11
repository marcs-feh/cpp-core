// A Bitfield is a linear collection of bits stored in a big-endian fashion.

#ifndef _bitfield_hpp_include_
#define _bitfield_hpp_include_

// TODO: Shift operations
#include <initializer_list>

#include "utils.hpp"
#include "types.hpp"
#include "assert.hpp"
#include "mem/allocator.hpp"

static inline
bool isBigEndian(){
	int n = 1;
	byte b = ((byte*)(&n))[0];
	return b == 0;
}

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

	// Bounds unchecked access when RELEASE_MODE is enabled
	constexpr
	u8 operator[](usize idx) const {
		Assert(idx < N, "Out of bounds access");
		usize byteIdx = (N / 8) - (idx / 8);
		usize bitOff = idx % 8;
		usize bitMask = 1 << bitOff;

		u8 b = (data[byteIdx] & bitMask) != 0;
		return b;
	}

	// Bounds checked access
	u8 get(usize idx) const {
		Panic_Assert(idx < N, "Out of bounds access to Bitfield");
		return operator[](idx);
	}

	// Returns if Bitfield has all of its bits on
	constexpr
	bool hasAll() const {
		usize bitOff = (cap() * 8) - len();
		for(usize i = 1; i <= cap() - 1; i += 1){
			if(data[cap() - i] != 0xff){ return false; }
		}

		return data[0] == (u8)(0xff >> bitOff);
	}

	// Returns if Bitfield has at least one bit on
	constexpr
	bool hasAny() const {
		usize bitOff = (cap() * 8) - len();
		for(usize i = 1; i <= cap() - 1; i += 1){
			if(data[cap() - i] != 0){ return true; }
		}

		// printf("bitoff: %zu data[0]:%x shift:%x\n", bitOff, data[0], (u8)(data[0] << bitOff));
		return ((u8)(data[0] << bitOff)) != 0;
	}

	// Set bit at position idx to v
	constexpr
	void set(usize idx, u8 v){
		if(idx >= N){ return; }
		usize byteIdx = (N / 8) - (idx / 8);
		usize bitOff = idx % 8;
		u8 b = (v != 0);

		data[byteIdx] &= ~(1 << bitOff);
		data[byteIdx] |= (b << bitOff);
	}

	// Flip bit at position idx
	constexpr
	void flip(usize idx){
		if(idx >= N){ return; }
		u8 b = operator[](idx);
		set(idx, !b);
	}

	constexpr
	Bitfield operator|(const Bitfield& bf){
		Bitfield<N> res;
		for(usize i = 0; i < cap(); i += 1){
			res.data[i] = bf.data[i] | data[i];
		}
		return res;
	}

	constexpr
	Bitfield operator~(){
		Bitfield<N> res;
		for(usize i = 0; i < cap(); i += 1){
			res.data[i] = ~data[i];
		}
		return res;
	}

	constexpr
	Bitfield operator&(const Bitfield& bf){
		Bitfield<N> res;
		for(usize i = 0; i < cap(); i += 1){
			res.data[i] = bf.data[i] & data[i];
		}
		return res;
	}

	constexpr
	Bitfield operator^(const Bitfield& bf){
		Bitfield<N> res;
		for(usize i = 0; i < cap(); i += 1){
			res.data[i] = bf.data[i] ^ data[i];
		}
		return res;
	}

	constexpr
	bool eq(const Bitfield &bf) const {
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

	template<typename T>
	constexpr
	bool eq(const std::initializer_list<T>& l) const {
		usize n = len() - 1;
		if(l.size() != len()){ return false; }

		for(auto&& e : l){
			if(bool(operator[](n)) != bool(e)){ return false; }
			if(n == 0){ break; }
			n -= 1;
		}

		return true;
	}

	bool operator==(const Bitfield &bf) const { return eq(bf); }

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
		usize n = min(len(), l.size());

		for(usize i = 0; i < cap(); i += 1){ data[i] = 0; }

		for(const auto& e : l){
			n -= 1;
			set(n, bool(e));
			if(n == 0){ break; }
		}
	}

	static_assert(N > 0, "Bitfield must be at least 1 wide");
};

// static inline
// void stringifyBits(char* buf, byte b){
// 	byte mask = 1;
// 	for(usize i = 0; i < 8; i += 1){
// 		buf[7 - i] = ((b >> i) & 1) ? '1' : '0';
// 	}
// 	buf[8] = 0;
// }
//
// template<typename T>
// static inline
// void displayBits(const T& x){
// 	const byte* bp = (byte*)(&x);
// 	char buf[9];
// 	printf("[%s] bits: %zu |", isBigEndian() ? "be" : "le", sizeof(T) * 8);
// 	for(usize i = 0; i < sizeof(T); i += 1){
// 		stringifyBits(buf, bp[i]);
// 		printf("%s|", buf);
// 	}
// 	printf("\n");
// }
#endif /* Include guard */
