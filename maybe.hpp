// Maybe indicates an optional value, attempting to extract a non-existing value
// causes a panic.

#ifndef _maybe_hpp_include_
#define _maybe_hpp_include_

#include "assert.hpp"
#include "utils.hpp"
#include <utility>
namespace core {

template<typename T>
struct Maybe {
	union {
		T data;
	};
	bool has_value;

	constexpr
	bool ok() const { return has_value; }

	constexpr
	operator bool() const { return has_value; }

	T&& get() && {
		Panic_Assert(has_value, "Maybe type has no data to get()");
		has_value = false;
		return move(data);
	}

	T& get() & {
		Panic_Assert(has_value, "Maybe type has no data to get()");
		has_value = false;
		return data;
	}

	const T& get() const& {
		Panic_Assert(has_value, "Maybe type has no data to get()");
		return data;
	}

	template<typename U>
	T get_or(U&& alt) && {
		if(!has_value){
			return static_cast<T>(forward<U>(alt));
		}
		return move(data);
	}

	template<typename U>
	T get_or(U&& alt) const& {
		if(!has_value){
			return static_cast<T>(forward<U>(alt));
		}
		return data;
	}

	void destroy(){
		if(has_value){
			data.~T();
		}
		has_value = false;
	}

	void operator=(T&& v){
		if(has_value){
			data = move(v);
		} else {
			new (&data) T(move(v));
		}
		has_value = true;
	}

	void operator=(const T& v){
		if(has_value){
			data = v;
		} else {
			new (&data) T(v);
		}
		has_value = true;
	}

	Maybe() : has_value{false} {}
	Maybe(T&& v) : data(move(v)), has_value{true} {}
	Maybe(const T& v) : data(v), has_value{true} {}

	Maybe(const Maybe<T>& opt) : has_value(opt.has_value) {
		if(has_value){
			new (&data) T(opt.get());
		}
	}

	Maybe(Maybe<T>&& opt) : has_value(opt.has_value) {
		if(has_value){
			new (&data) T(move(opt).get());
			opt.has_value = false;
		}
	}

	void operator=(const Maybe<T>& opt){
		if(opt.has_value){
			*this = opt.get();
		} else {
			destroy();
		}
	}

	void operator=(Maybe<T>&& opt){
		if(opt.has_value){
			*this = move(opt).get();
			opt.has_value = false;
		} else {
			destroy();
		}
	}

	~Maybe(){
		if(has_value){ data.~T(); }
	}
};

}

#endif /* Include guard */
