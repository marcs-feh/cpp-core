// Generalization of a N dimensional vector of type T. This has *ZERO* bounds
// checking.

#ifndef _vecn_hpp_include_
#define _vecn_hpp_include_

#include <cmath>
#include "types.hpp"

namespace vec {

template<typename T, usize N>
struct VecN {
	T data[N];

	constexpr usize len() const { return N; }

	constexpr
	T& operator[](usize idx) { return data[idx]; };

	constexpr
	const T& operator[](usize idx) const { return data[idx]; };
};

template<typename T, usize N>
constexpr
T mag(const VecN<T,N>& v){
	T acc = 0;
	for(usize i = 0; i < v.len(); i += 1){
		acc += (v.data[i] * v.data[i]);
	}
	return std::sqrt(acc);
}

template<typename T, usize N>
constexpr
VecN<T,N> operator+(const VecN<T,N>& a, const VecN<T,N>& b){
	VecN<T, N> v = a;
	for(usize i = 0; i < a.len(); i += 1){
		v.data[i] += b.data[i];
	}
	return v;
}

template<typename T, usize N>
constexpr
VecN<T,N> operator-(const VecN<T,N>& a, const VecN<T,N>& b){
	VecN<T, N> v = a;
	for(usize i = 0; i < a.len(); i += 1){
		v.data[i] -= b.data[i];
	}
	return v;
}

template<typename T, usize N>
constexpr
T operator*(const VecN<T,N>& a, const VecN<T,N>& b){
	T acc = 0;
	for(usize i = 0; i < a.len(); i += 1){
		acc += (a.data[i] * b.data[i]);
	}
	return acc;
}


template<typename T, usize N>
constexpr
bool operator==(const VecN<T,N>& a, const VecN<T,N>& b){
	for(usize i = 0; i < N; i += 1){
		if(a[i] != b[i]){ return false; }
	}
	return true;
}

}
#endif /* Include guard */
