// A result type is a tagged union between a ok type and some other error type.
// It is similar in purpose to Maybe, but allows for further flexibility when it
// comes to error handling.

#ifndef _result_hpp_include_
#define _result_hpp_include_

#include "assert.hpp"
#include "utils.hpp"

template<typename T, typename E>
struct Result {
	union {
		T data;
		E error;
	};
	bool is_error;

	constexpr bool ok() const { return !is_error; }
	constexpr operator bool() { return !is_error; }

	// Data access
	T& get() & {
		Panic_Assert(!is_error, "Cannot access error value with get()");
		return data;
	}

	T&& get() && {
		Panic_Assert(!is_error, "Cannot access error value with get()");
		return move(data);
	}

	const T& get() const& {
		Panic_Assert(!is_error, "Cannot access error value with get()");
		return data;
	}

	// Error access
	E& err() & {
		Panic_Assert(is_error, "Cannot access non-error value with err()");
		return error;
	}

	E&& err() && {
		Panic_Assert(is_error, "Cannot access non-error value with err()");
		return move(error);
	}

	const E& err() const& {
		Panic_Assert(is_error, "Cannot access non-error value with err()");
		return error;
	}

	template<typename U>
	T get_or(U&& alt) const& {
		if(is_error){
			return static_cast<T>(forward<U>(alt));
		}
		return data;
	}

	template<typename U>
	T get_or(U&& alt) && {
		if(is_error){
			return static_cast<T>(forward<U>(alt));
		}
		return move(data);
	}

	// Value set
	void operator=(const T& v){
		if(is_error){
			error.~E();
			new (&data) T(v);
		} else {
			data = v;
		}
		is_error = false;
	}
	void operator=(T&& v){
		if(is_error){
			error.~E();
			new (&data) T(move(v));
		} else {
			data = move(v);
		}
		is_error = false;
	}

	// Error set
	void operator=(const E& e){
		if(is_error){
			data.~T();
			new (&error) E(e);
		} else {
			error = e;
		}
		is_error = true;
	}

	void operator=(E&& e){
		if(is_error){
			data.~T();
			new (&error) E(move(e));
		} else {
			error = move(e);
		}
		is_error = true;
	}

	Result() : error(), is_error(true){}

	Result(const E& e) : error(e), is_error(true) {}
	Result(E&& e) : error(move(e)), is_error(true) {}

	Result(const T& v) : data(v), is_error(false){}
	Result(T&& v) : data(move(v)), is_error(false){}

	Result(Result&& r) : is_error(r.is_error){
		if(is_error){
			new (&error) E(move(r.error));
		} else {
			new (&data) T(move(r.data));
		}
	}

	void operator=(Result&& r){
		if(r.is_error){
			if(is_error){
				error = move(r).error;
			} else {
				data.~T();
				new (&error) E(move(r).error);
			}
		}
		else {
			if(is_error){
				error.~E();
				new (&data) T(move(r).data);
			} else {
				data = move(r).data;
			}
		}
		is_error = r.is_error;
	}

	void operator=(const Result& r){
		if(r.is_error){
			if(is_error){
				error = r.error;
			} else {
				data.~T();
				new (&error) E(r.error);
			}
		}
		else {
			if(is_error){
				error.~E();
				new (&data) T(r.data);
			} else {
				data = r.data;
			}
		}

		is_error = r.is_error;
	}

	~Result(){
		if(is_error){ error.~E(); }
		else { data.~T(); }
	}
};

#endif /* Include guard */
