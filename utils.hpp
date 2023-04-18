#ifndef _utils_hpp_include_
#define _utils_hpp_include_

// TODO: foward, exchange

template<typename T>
struct DelReference { typedef T Type;};
template<typename T>
struct DelReference<T&> { typedef T Type;};
template<typename T>
struct DelReference<T&&>{ typedef T Type;};

template<typename T>
typename DelReference<T>::Type&& move(T&& x){
	typedef typename DelReference<T>::Type&& RvalRef;
	return static_cast<RvalRef>(x);
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
