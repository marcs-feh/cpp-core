#ifndef _static_list_hpp_include_
#define _static_list_hpp_include_

#include "types.hpp"
#include "utils.hpp"
#include "assert.hpp"
#include "slice.hpp"

namespace core {

template<typename T, usize N>
struct StaticList {
	usize lenght = 0;
	union {
		T data[N];
	};

	constexpr usize len() const { return lenght; }
	constexpr usize cap() const { return N; }

	template<typename U>
	constexpr
	void push(U&& x){
		if((lenght + 1) > N){ return; }
		new (&data[lenght]) T(static_cast<T>(forward<U>(x)));
		lenght += 1;
		return;
	}

	void pop(){
		if(lenght == 0){ return; }
		lenght -= 1;
		data[lenght].~T();
	}

	void insert(const T& x, usize idx){
		if((lenght + 1) > N){
			Assert(idx < lenght, "Index out of bounds");
			return;
		}
		push(x);
		for(usize i = lenght - 1; i > idx; i -= 1){
			swap(data[i], data[i - 1]);
		}
	}

	// Does nothing on idx out of bounds on RELEASE_MODE
	void remove(usize idx){
		if(idx >= lenght){
			Assert(idx < lenght, "Index out of bounds");
			return;
		}

		for(usize i = idx + 1; i < lenght; i += 1){
			swap(data[i], data[i - 1]);
		}
		pop();
		return;
	}

	const T& at(usize idx) const {
		Panic_Assert(idx < lenght, "Out of bounds access");
		return data[idx];
	}

	T& operator[](usize idx){
		Assert(idx < lenght, "Out of bounds access");
		return data[idx];
	}

	const T& operator[](usize idx) const {
		Assert(idx < lenght, "Out of bounds access");
		return data[idx];
	}

	StaticList(){};

	StaticList(const StaticList& s) : lenght(s.lenght) {
		for(usize i = 0; i < s.lenght; i += 1){
			push(s.data[i]);
		}
	}

	StaticList& operator=(const StaticList& s){
		if(s.lenght >= lenght){
			usize rest = s.lenght - lenght;
			// Assign what's already initialized, then push the rest
			for(usize i = 0; i < lenght; i += 1){
				data[i] = s.data[i];
			}
			for(usize i = 0; i < rest; i += 1){
				push(s.data[i]);
			}
		} else {
			usize diff = lenght - s.lenght;
			// Delete excess, then assign to self
			for(usize i = 0; i < diff; i += 1){
			pop();
			}
			for(usize i = 0; i < s.lenght; i += 1){
				data[i] = s.data[i];
			}
		}
		lenght = s.lenght;
	}

	StaticList(StaticList&& s){
		for(usize i = 0; i < s.lenght; i += 1){
			push(move(s.data[i]));
		}
		lenght = exchange(s.lenght, 0);
	}

	StaticList& operator=(StaticList&& s){
		if(s.lenght >= lenght){
			usize rest = s.lenght - lenght;
			// Assign what's already initialized, then push the rest
			for(usize i = 0; i < lenght; i += 1){
				data[i] = move(s.data[i]);
			}
			for(usize i = 0; i < rest; i += 1){
				push(move(s.data[i]));
			}
		} else {
			usize diff = lenght - s.lenght;
			// Delete excess, then assign to self
			for(usize i = 0; i < diff; i += 1){
			pop();
			}
			for(usize i = 0; i < s.lenght; i += 1){
				data[i] = move(s.data[i]);
			}
		}
		lenght = exchange(s.lenght, 0);
	}

	~StaticList(){
		while(lenght > 0){ pop(); }
	}
};

template<typename T, usize N>
constexpr
bool operator==(const StaticList<T,N>& l, const StaticList<T,N>& r){
	if(l.lenght != r.lenght){ return false; }
	for(usize i = 0; i < l.lenght; i += 1){
		if(l.data[i] != r.data[i]){ return false; }
	}
	return true;
}
template<typename T, usize N>
constexpr
bool operator!=(const StaticList<T,N>& l, const StaticList<T,N>& r){
	return !(l == r);
}
}



#endif /* Include guard */
