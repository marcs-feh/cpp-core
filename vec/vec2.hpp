#ifndef _vec2_hpp_include_
#define _vec2_hpp_include_

#include "types.hpp"
#include <cmath>

namespace vec {

template<typename T>
struct Vec2 {
	T x, y;

	constexpr usize len() const { return 2; }

	constexpr
	Vec2() = default;
	constexpr
	Vec2(const T& x, const T& y) : x(x), y(y) {};
};

template<typename T>
constexpr
T mag(const Vec2<T>& v){
	return std::sqrt((v.y * v.y) + (v.x * v.x));
}

template<typename T>
constexpr
Vec2<T> operator+(const Vec2<T>& a, const Vec2<T>& b){
	return Vec2<T>(a.x + b.x, a.y + b.y);
}

template<typename T>
constexpr
Vec2<T> operator-(const Vec2<T>& a, const Vec2<T>& b){
	return Vec2<T>(a.x - b.x, a.y - b.y);
}

template<typename T>
constexpr
T operator*(const Vec2<T>& a, const Vec2<T>& b){
	return (a.x * b.x) + (a.y * b.y);
}

template<typename T>
constexpr
bool operator==(const Vec2<T>& a, const Vec2<T>& b){
	return (a.x == b.x) && (a.y == b.y);
}

}


#endif /* Include guard */
