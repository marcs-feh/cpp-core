#include "types.hpp"
#include <cmath>

namespace core {
struct Complex64 {
	f32 real = 0;
	f32 imag = 0;

	constexpr Complex64(){}
	constexpr Complex64(f32 r, f32 i) : real(r), imag(i) {}
};

struct Complex128 {
	f64 real = 0;
	f64 imag = 0;

	constexpr Complex128(){}
	constexpr Complex128(f64 r, f64 i) : real(r), imag(i) {}
};

// Complex64
static constexpr
f32 abs(const Complex64 &z){
	return std::sqrt((z.real * z.real) + (z.imag * z.imag));
}

constexpr static
Complex64 operator+(const Complex64& a, const Complex64& b){
	Complex64 r = {
		a.real + b.real,
		a.imag + b.imag
	};
	return r;
}

constexpr static
Complex64 operator-(const Complex64& a, const Complex64& b){
	Complex64 r = {
		a.real - b.real,
		a.imag - b.imag,
	};
	return r;
}

constexpr static
Complex64 operator*(const Complex64& a, const Complex64& b){
	Complex64 r = {
		(a.real * b.real) - (a.imag * b.imag),
		(a.real * b.imag) + (a.imag * b.real),
	};
	return r;
}

constexpr static
Complex64 operator/(const Complex64& a, const Complex64& b){
	const f32 deno = (b.real * b.real) + (b.imag * b.imag);
	// TODO: fix division by 0
	Complex64 r = {
		((a.real * b.real) + (a.imag * b.imag)) / deno,
		((a.imag * b.real) - (a.real * b.imag)) / deno,
	};
	return r;
}

constexpr static
Complex128 operator+(const Complex128& a, const Complex128& b){
	Complex128 r = {
		a.real + b.real,
		a.imag + b.imag,
	};
	return r;
}

constexpr static
bool operator==(const Complex64& a, const Complex64& b){
	bool r = (a.real == b.real) && (a.imag == b.imag);
	return r;
}

// Complex128
static constexpr
f64 abs(const Complex128 &z){
	return std::sqrt((z.real * z.real) + (z.imag * z.imag));
}

constexpr static
Complex128 operator-(const Complex128& a, const Complex128& b){
	Complex128 r = {
		a.real - b.real,
		a.imag - b.imag,
	};
	return r;
}

constexpr static
Complex128 operator*(const Complex128& a, const Complex128& b){
	Complex128 r = {
		(a.real * b.real) - (a.imag * b.imag),
		(a.real * b.imag) + (a.imag * b.real),
	};
	return r;
}

constexpr static
Complex128 operator/(const Complex128& a, const Complex128& b){
	f64 deno = (b.real * b.real) + (b.imag * b.imag);
	// TODO: fix division by 0
	Complex128 r = {
		((a.real * b.real) + (a.imag * b.imag)) / deno,
		((a.imag * b.real) - (a.real * b.imag)) / deno,
	};
	return r;
}

constexpr static
bool operator==(const Complex128& a, const Complex128& b){
	bool r = (a.real == b.real) && (a.imag == b.imag);
	return r;
}
}

