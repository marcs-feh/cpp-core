#ifndef _utils_hpp_include_
#define _utils_hpp_include_

// TODO: exchange

template<typename T>
struct DelReference { typedef T Type;};
template<typename T>
struct DelReference<T&> { typedef T Type;};
template<typename T>
struct DelReference<T&&>{ typedef T Type;};

// Transforms something into an r-value reference.
template<typename T>
typename DelReference<T>::Type&& move(T&& x){
	typedef typename DelReference<T>::Type&& RvalRef;
	return static_cast<RvalRef>(x);
}

// Contitionally moves x, if and only if, x is an r-value reference. Requires
// passing template type explicitly.
template<typename T>
T&& forward(DelReference<T>& x){
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
