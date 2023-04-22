// Misc. utilities, mostly template stuff

#ifndef _utils_hpp_include_
#define _utils_hpp_include_

template<typename T>
struct DelReference { typedef T Type;};
template<typename T>
struct DelReference<T&> { typedef T Type;};
template<typename T>
struct DelReference<T&&>{ typedef T Type;};

// Used to create an integral constant
template<typename T, T v>
struct IntegralConst {
	static constexpr T value = v;
	typedef T ValueType;
	constexpr operator ValueType() { return value; }
};

using FalseType = IntegralConst<bool, false>;
using TrueType  = IntegralConst<bool, true>;

template<typename T>
struct IsLvalRefType : FalseType {};
template<typename T>
struct IsLvalRefType<T&> : TrueType {};
template<typename T>
struct IsLvalRefType<T&&> : FalseType {};

template<typename T>
struct IsRvalRefType : FalseType {};
template<typename T>
struct IsRvalRefType<T&> : FalseType {};
template<typename T>
struct IsRvalRefType<T&&> : TrueType {};

template<typename T>
static constexpr bool isLvalRef = IsLvalRefType<T>::value;

template<typename T>
static constexpr bool isRvalRef = IsRvalRefType<T>::value;

// Transforms something into an r-value reference.
template<typename T>
constexpr
typename DelReference<T>::Type&& move(T&& x){
	typedef typename DelReference<T>::Type&& RvalRef;
	return static_cast<RvalRef>(x);
}

// Contitionally moves x, if and only if, x is an r-value reference. Requires
// passing template type explicitly.
template<typename T>
constexpr
T&& forward(typename DelReference<T>::Type& x){
	return static_cast<T&&>(x);
}

// Contitionally moves x, if and only if, x is an r-value reference. Requires
// passing template type explicitly.
template<typename T>
constexpr
T&& forward(typename DelReference<T>::Type&& x){
	static_assert(!isLvalRef<T>, "Cannot forward lvalue to rvalue reference");
	return static_cast<T&&>(x);
}

template<typename T>
const T& max(const T& a, const T& b){
	if(a > b){ return a; }
	return b;
}

template<typename T>
const T& min(const T& a, const T& b){
	if(a < b){ return a; }
	return b;
}

template<typename Tl, typename Tr>
struct Pair {
	Tl left;
	Tr right;
};

#endif /* Include guard */
