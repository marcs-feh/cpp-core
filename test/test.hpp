#ifndef _test_hpp_include_
#define _test_hpp_include_

#include "types.hpp"
#include <cstdio>

struct Test {
	uint test_count;
	uint fail_count;
	const char* title;

	void show_title(){
		std::printf("[ %s%s%s ]\n", white, title, reset);
	}

	void assert_expr(bool expr, const char* msg){
		test_count += 1;
		if(!expr){
			fail_count += 1;
			std::printf("  Failed: %s\n", msg);
		}
	}

	void show_results(){
		if(fail_count > 0){
			std::printf("%sFAIL%s", red, reset);
		} else {
			std::printf("%sPASS%s", green, reset);
		}
		std::printf(": ok in %d out of %d tests.\n",
							  test_count - fail_count, test_count);
	}

	Test(const char* title) : test_count{0}, fail_count{0}, title(title){
		show_title();
	}

	~Test(){
		show_results();
	}

	static constexpr char const* red   = "\e[0;31m";
	static constexpr char const* green = "\e[0;32m";
	static constexpr char const* white = "\e[1;37m";
	static constexpr char const* reset = "\e[0m";
};

// Test Predicate macro, assumes a test named T
#define Tp(expr) do { T.assert_expr((expr), #expr); } while(0);
#define T_Log(fmt, ...) std::printf("  >> " fmt "\n", __VA_ARGS__)

#endif /* Include guard */
