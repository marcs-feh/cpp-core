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
	bool isErr;

	constexpr bool ok() const { return !isErr; }
	constexpr operator bool() { return !isErr; }

	// Data access
	T& get() & {
		Panic_Assert(!isErr, "Cannot access error value with get()");
		return data;
	}

	T&& get() && {
		Panic_Assert(!isErr, "Cannot access error value with get()");
		return move(data);
	}

	const T& get() const& {
		Panic_Assert(!isErr, "Cannot access error value with get()");
		return data;
	}

	// Error access
	E& err() & {
		Panic_Assert(isErr, "Cannot access non-error value with err()");
		return error;
	}

	E&& err() && {
		Panic_Assert(isErr, "Cannot access non-error value with err()");
		return move(error);
	}

	const E& err() const& {
		Panic_Assert(isErr, "Cannot access non-error value with err()");
		return error;
	}

	template<typename U>
	T getOr(U&& alt) const& {
		if(isErr){
			return static_cast<T>(forward<U>(alt));
		}
		return data;
	}

	template<typename U>
	T getOr(U&& alt) && {
		if(isErr){
			return static_cast<T>(forward<U>(alt));
		}
		return move(data);
	}

	// Value set
	void operator=(const T& v){
		if(isErr){
			error.~E();
			new (&data) T(v);
		} else {
			data = v;
		}
		isErr = false;
	}
	void operator=(T&& v){
		if(isErr){
			error.~E();
			new (&data) T(move(v));
		} else {
			data = move(v);
		}
		isErr = false;
	}

	// Error set
	void operator=(const E& e){
		if(isErr){
			data.~T();
			new (&error) E(e);
		} else {
			error = e;
		}
		isErr = true;
	}

	void operator=(E&& e){
		if(isErr){
			data.~T();
			new (&error) E(move(e));
		} else {
			error = move(e);
		}
		isErr = true;
	}

	Result() : error(), isErr(true){}

	Result(const E& e) : error(e), isErr(true) {}
	Result(E&& e) : error(move(e)), isErr(true) {}

	Result(const T& v) : data(v), isErr(false){}
	Result(T&& v) : data(move(v)), isErr(false){}

	Result(Result&& r) : isErr(r.isErr){
		if(isErr){
			new (&error) E(move(r.error));
		} else {
			new (&data) T(move(r.data));
		}
	}

	void operator=(Result&& r){
		if(r.isErr){
			if(isErr){
				error = move(r).error;
			} else {
				data.~T();
				new (&error) E(move(r).error);
			}
		}
		else {
			if(isErr){
				error.~E();
				new (&data) T(move(r).data);
			} else {
				data = move(r).data;
			}
		}
		isErr = r.isErr;
	}

	void operator=(const Result& r){
		if(r.isErr){
			if(isErr){
				error = r.error;
			} else {
				data.~T();
				new (&error) E(r.error);
			}
		}
		else {
			if(isErr){
				error.~E();
				new (&data) T(r.data);
			} else {
				data = r.data;
			}
		}

		isErr = r.isErr;
	}

	~Result(){
		if(isErr){ error.~E(); }
		else { data.~T(); }
	}
};

#endif /* Include guard */
