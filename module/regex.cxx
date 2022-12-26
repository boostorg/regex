
module;

#if defined(_WIN32) && __has_include(<windows.h>)
#include <windows.h>
#endif
#include <cctype>
#include <cstddef>
#include <cwctype>
#include <cassert>

#ifdef __cpp_lib_modules
import std;
#elif defined(MSVC_EXPERIMENTAL_STD_MODULE)
import std.core;
#else
#include <cassert>
#include <cstdint>
#include <climits>
#include <cctype>
#include <cstddef>
#include <cwctype>
#include <climits>
#include <cstring>

#include <vector>
#include <set>
#include <locale>
#include <type_traits>
#include <ios>
#include <istream>
#include <functional>
#include <iterator>
#include <new>
#include <atomic>
#include <memory>
#include <map>
#include <list>
#include <stdexcept>
#include <string>
#include <functional>
#include <algorithm>
#include <locale>
#include <limits>
#include <cstdint>
#include <sstream>
#include <ios>
#ifdef BOOST_HAS_THREADS
#include <mutex>
#endif
#endif


#if __has_include(<unicode/utypes.h>)
#include <unicode/utypes.h>
#include <unicode/uchar.h>
#include <unicode/coll.h>
#endif

#define BOOST_REGEX_AS_MODULE
#define BOOST_REGEX_STANDALONE
#define BOOST_REGEX_MODULE_EXPORT export

export module boost.regex;

#include <boost/regex.hpp>

#if __has_include(<unicode/utypes.h>)
#include <boost/regex/icu.hpp>
#endif
