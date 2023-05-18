#ifndef _vec3_hpp_include_
#define _vec3_hpp_include_

#include "types.hpp"
#include <cmath>

namespace vec {

template<typename T>
struct Vec3 {
	T x, y, z;

	constexpr usize len() const { return 3; }

	constexpr
	Vec3() = default;
	constexpr
	Vec3(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {};
};

template<typename T>
constexpr
T mag(const Vec3<T>& v){
	return std::sqrt((v.y * v.y) + (v.x * v.x) + (v.z * v.z));
}

template<typename T>
constexpr
Vec3<T> operator+(const Vec3<T>& a, const Vec3<T>& b){
	return Vec3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}

template<typename T>
constexpr
Vec3<T> operator-(const Vec3<T>& a, const Vec3<T>& b){
	return Vec3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
}

template<typename T>
constexpr
T operator*(const Vec3<T>& a, const Vec3<T>& b){
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

template<typename T>
constexpr
bool operator==(const Vec3<T>& a, const Vec3<T>& b){
	return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}

}

#endif /* Include guard */
