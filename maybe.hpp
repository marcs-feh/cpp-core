#ifndef _maybe_hpp_include_
#define _maybe_hpp_include_

#include "assert.hpp"
#include "utils.hpp"
#include <utility>

template<typename T>
struct Maybe {
	union {
		T data;
	};
	bool hasVal;

	bool ok() const { return hasVal; }

	T&& get(){
		Panic_Assert(hasVal, "Maybe type has no data to get()");
		hasVal = false;
		return move(data);
	}

	template<typename U>
	T&& getOr(U&& alt){
		if(!hasVal){ return move(alt); }
		return move(data);
	}

	Maybe() : hasVal{false} {}
	Maybe(T&& v) : data(move(v)), hasVal{true} {}
	Maybe(const T& v) : data(v), hasVal{true} {}

	void operator=(T&& v){
		if(hasVal){
			data = move(v);
		} else {
			new (&data) T(move(v));
		}
		hasVal = true;
	}

	void operator=(const T& v){
		if(hasVal){
			data = v;
		} else {
			new (&data) T(v);
		}
		hasVal = true;
	}

	Maybe(const Maybe<T>&) = delete;
	Maybe(Maybe<T>&&) = delete;

	~Maybe(){
		if(hasVal){ data.~T(); }
	}
};


#endif /* Include guard */
