/*
 *
 * Copyright (c) 2004
 * Dr John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */
 
 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex_traits_defaults.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares API's for access to regex_traits default properties.
  */

#ifndef BOOST_REGEX_TRAITS_DEFAULTS_HPP_INCLUDED
#define BOOST_REGEX_TRAITS_DEFAULTS_HPP_INCLUDED

namespace boost{ namespace re_detail{

const char* get_default_syntax(regex_constants::syntax_type n);
const char* get_default_error_string(regex_constants::error_type n);

// is charT c a combining character?
bool is_combining_implementation(uint_least16_t s);

template <class charT>
inline bool is_combining(charT c)
{
   return (c < 0) ? false : ((c > (std::numeric_limits<uint_least16_t>::max)()) ? false : is_combining_implementation(static_cast<unsigned short>(c)));
}
template <>
inline bool is_combining<char>(char)
{
   return false;
}
template <>
inline bool is_combining<signed char>(signed char)
{
   return false;
}
template <>
inline bool is_combining<unsigned char>(unsigned char)
{
   return false;
}
#if defined(WCHAR_MIN) && (WCHAR_MIN == 0) && !defined(BOOST_NO_INTRINSIC_WCHAR_T)
#if defined(WCHAR_MAX) && (WCHAR_MAX <= USHRT_MAX)
template<>
inline bool is_combining<wchar_t>(wchar_t c)
{
   return is_combining_implementation(static_cast<unsigned short>(c));
}
#else
template<>
inline bool is_combining<wchar_t>(wchar_t c)
{
   return (c > std::numeric_limits<uint_least16_t>::max()) ? false : is_combining_implementation(static_cast<unsigned short>(c));
}
#endif
#endif

//
// is a charT c a line separator?
//
template <class charT>
inline bool is_separator(charT c)
{
   return BOOST_REGEX_MAKE_BOOL((c == '\n') || (c == '\r'));
}

//
// parse_value:
// covert a character sequence into a value, return -1 if no digits found:
//
template <class ForwardIterator, class traits>
int parse_value(ForwardIterator& p1, ForwardIterator p2, const traits& traits_inst, int radix = 10)
{
   int value = 0;
   if(traits_inst.value(*p1) < 0)
      return -1;
   while(p1 != p2)
   {
      int v2 = traits_inst.value(*p1);
      if(v2 < 0) break;
      value *= radix;
      value += v2;
      ++p1;
   }
   return value;
}


} // re_detail
} // boost

#endif
