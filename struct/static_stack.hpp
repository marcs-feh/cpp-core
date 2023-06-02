#ifndef _static_stack_hpp_include_
#define _static_stack_hpp_include_

#include "types.hpp"
#include "utils.hpp"
#include "assert.hpp"
#include "slice.hpp"
#include "maybe.hpp"

namespace core {

template<typename T, usize N>
struct StaticStack {
	usize lenght = 0;
	union {
		T data[N];
	};

	constexpr usize len() const { return lenght; }
	constexpr usize cap() const { return N; }

	template<typename U>
	constexpr
	void push(U&& x){
		if((lenght + 1) > N){
			Assert(lenght > 0, "Stack overflow"); return;
		}
		new (&data[lenght]) T(static_cast<T>(forward<U>(x)));
		lenght += 1;
	}

	// Moves top of stack to x
	void pop(T& x){
		if(lenght == 0){
			Assert(lenght > 0, "Stack underflow"); return;
		}
		lenght -= 1;
		x = move(data[lenght]);
		data[lenght].~T();
	}

	// Destroy top of stack
	void pop(){
		if(lenght == 0){
			Assert(lenght > 0, "Stack underflow"); return;
		}
		lenght -= 1;
		data[lenght].~T();
	}

	// Copy of stack top
	Maybe<T> top(){
		Maybe<T> opt;
		if(lenght == 0){ return opt; }
		opt = data[lenght - 1];
		return opt;
	}

	StaticStack(){}

	StaticStack(const StaticStack& s) : lenght(s.lenght) {
		for(usize i = 0; i < s.lenght; i += 1){
			push(s.data[i]);
		}
	}

	StaticStack& operator=(const StaticStack& s){
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

	StaticStack(StaticStack&& s){
		for(usize i = 0; i < s.lenght; i += 1){
			push(move(s.data[i]));
		}
		lenght = exchange(s.lenght, 0);
	}

	StaticStack& operator=(StaticStack&& s){
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

	~StaticStack(){
		while(lenght > 0){ pop(); }
	}
};

template<typename T, usize N>
constexpr
bool operator==(const StaticStack<T,N>& l, const StaticStack<T,N>& r){
	if(l.lenght != r.lenght){ return false; }
	for(usize i = 0; i < l.lenght; i += 1){
		if(l.data[i] != r.data[i]){ return false; }
	}
	return true;
}
}

#endif /* Include guard */
