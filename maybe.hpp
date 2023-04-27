// Maybe indicates an optional value, attempting to extract a non-existing value
// causes a panic.

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

	constexpr
	bool ok() const { return hasVal; }

	constexpr
	operator bool() const { return hasVal; }

	T&& get() && {
		panicAssert(hasVal, "Maybe type has no data to get()");
		hasVal = false;
		return move(data);
	}

	T& get() & {
		panicAssert(hasVal, "Maybe type has no data to get()");
		hasVal = false;
		return data;
	}

	const T& get() const& {
		panicAssert(hasVal, "Maybe type has no data to get()");
		return data;
	}

	template<typename U>
	T getOr(U&& alt) const& {
		if(!hasVal){
			return static_cast<T>(forward<U>(alt));
		}
		return data;
	}

	template<typename U>
	T getOr(U&& alt) && {
		if(!hasVal){
			return static_cast<T>(forward<U>(alt));
		}
		return move(data);
	}

	void destroy(){
		if(hasVal){
			data.~T();
		}
		hasVal = false;
	}

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

	Maybe() : hasVal{false} {}
	Maybe(T&& v) : data(move(v)), hasVal{true} {}
	Maybe(const T& v) : data(v), hasVal{true} {}

	Maybe(const Maybe<T>& opt) : hasVal(opt.hasVal) {
		if(hasVal){
			new (&data) T(opt.get());
		}
	}

	Maybe(Maybe<T>&& opt) : hasVal(opt.hasVal) {
		if(hasVal){
			new (&data) T(move(opt).get());
			opt.hasVal = false;
		}
	}

	void operator=(const Maybe<T>& opt){
		if(opt.hasVal){
			*this = opt.get();
		} else {
			destroy();
		}
	}

	void operator=(Maybe<T>&& opt){
		if(opt.hasVal){
			*this = move(opt).get();
			opt.hasVal = false;
		} else {
			destroy();
		}
	}

	~Maybe(){
		if(hasVal){ data.~T(); }
	}
};

#endif /* Include guard */
