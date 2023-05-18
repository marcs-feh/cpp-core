#ifndef _vec4_hpp_include_
#define _vec4_hpp_include_

#include "types.hpp"
#include <cmath>

namespace vec {

template<typename T>
struct Vec4 {
	T x, y, z, w;

	constexpr usize len() const { return 4; }

	constexpr
	Vec4() = default;

	constexpr
	Vec4(const T &x, const T &y, const T &z, const T &w)
	: x(x), y(y), z(z), w(w){};
};

template<typename T>
constexpr
T mag(const Vec4<T>& v){
	return std::sqrt((v.y * v.y) + (v.x * v.x) + (v.z * v.z) + (v.w * v.w));
}

template<typename T>
constexpr
Vec4<T> operator+(const Vec4<T>& a, const Vec4<T>& b){
	return Vec4<T>(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

template<typename T>
constexpr
Vec4<T> operator-(const Vec4<T>& a, const Vec4<T>& b){
	return Vec4<T>(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

template<typename T>
constexpr
T operator*(const Vec4<T>& a, const Vec4<T>& b){
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

template<typename T>
constexpr
bool operator==(const Vec4<T>& a, const Vec4<T>& b){
	return (a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w);
}

}


#endif /* Include guard */
