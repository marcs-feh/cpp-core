#ifndef _source_loc_hpp_include_
#define _source_loc_hpp_include_

#include "types.hpp"

namespace core {
struct SourceLocation {
	const char* filename = nullptr;
	u32 line = 1;
};
}

#define Source_Here() SourceLocation{.filename = __FILE__, .line = __LINE__}

#endif /* Include guard */
