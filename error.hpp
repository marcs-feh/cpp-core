#ifndef _error_hpp_include_
#define _error_hpp_include_

// TODO: add errorlike concept
// TODO: string fmt
// TODO: get rid of cstdio
#include "types.hpp"
#include "source_loc.hpp"
#include <cstdio>

namespace core {
struct Error {
	const char* desc;
	SourceLocation loc;
};

static inline
void explain_stderr(const Error& e){
	if(e.loc.filename){
		std::fprintf(stderr, "[Error %s:%d] ", e.loc.filename, e.loc.line);
	} else {
		std::fprintf(stderr, "[Error ] ");
	}

	if(e.desc){
		std::fprintf(stderr, "%s\n", e.desc);
	} else {
		std::fprintf(stderr, "(no description)\n");
	}
}

}

#endif /* Include guard */
