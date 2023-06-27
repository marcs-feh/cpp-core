// Misc compile time constants

#ifndef _consts_hpp_include_
#define _consts_hpp_include_

#include "types.hpp"

namespace core {

namespace math {
constexpr f64 pi    = 3.141592653589793115997963468544185161590576171875;
constexpr f64 euler = 2.718281828459045235360287471352662497757247093699;
constexpr f64 phi   = 1.618033988749894848204586834365638117720309179805;
}

namespace prefix {
constexpr usize kibi = 1024;
constexpr usize mebi = 1024 * kibi;
constexpr usize gibi = 1024 * mebi;
constexpr usize tebi = 1024 * gibi;
constexpr usize pebi = 1024 * tebi;
constexpr usize exbi = 1024 * pebi;

constexpr usize kilo = 1000;
constexpr usize mega = 1000 * kilo;
constexpr usize giga = 1000 * mega;
constexpr usize tera = 1000 * giga;
constexpr usize peta = 1000 * tera;
constexpr usize exa  = 1000 * peta;
}
}

#endif /* Include guard */
