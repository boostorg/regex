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

BOOST_REGEX_DECL const char* BOOST_REGEX_CALL get_default_syntax(regex_constants::syntax_type n);
BOOST_REGEX_DECL const char* BOOST_REGEX_CALL get_default_error_string(regex_constants::error_type n);

// is charT c a combining character?
BOOST_REGEX_DECL bool BOOST_REGEX_CALL is_combining_implementation(uint_least16_t s);

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
#ifdef _MSC_VER
template<>
inline bool is_combining<wchar_t>(wchar_t c)
{
   return is_combining_implementation(static_cast<unsigned short>(c));
}
#elif defined(WCHAR_MIN) && (WCHAR_MIN == 0) && !defined(BOOST_NO_INTRINSIC_WCHAR_T)
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
   return (c > (std::numeric_limits<uint_least16_t>::max)()) ? false : is_combining_implementation(static_cast<unsigned short>(c));
}
#endif
#endif

//
// is a charT c a line separator?
//
template <class charT>
inline bool is_separator(charT c)
{
   return BOOST_REGEX_MAKE_BOOL((c == '\n') || (c == '\r') || (static_cast<int>(c) == 0x2028) || (static_cast<int>(c) == 0x2029));
}

//
// get a default collating element:
//
BOOST_REGEX_DECL std::string BOOST_REGEX_CALL lookup_default_collate_name(const std::string& name);

//
// get the id of a character clasification, the individual
// traits classes then transform that id into a bitmask:
//
template <class charT>
struct character_pointer_range
{
   const charT* p1;
   const charT* p2;

   bool operator < (const character_pointer_range& r)const
   {
      return std::lexicographical_compare(p1, p2, r.p1, r.p2);
   }
   bool operator == (const character_pointer_range& r)const
   {
      return (std::distance(p1, p2) == std::distance(r.p1, r.p2)) && std::equal(p1, p2, r.p1);
   }
};
template <class charT>
int get_default_class_id(const charT* p1, const charT* p2)
{
   static const charT data[] = {
      'a', 'l', 'n', 'u', 'm',
      'a', 'l', 'p', 'h', 'a',
      'b', 'l', 'a', 'n', 'k',
      'c', 'n', 't', 'r', 'l',
      'd', 'i', 'g', 'i', 't',
      'g', 'r', 'a', 'p', 'h',
      'l', 'o', 'w', 'e', 'r',
      'p', 'r', 'i', 'n', 't',
      'p', 'u', 'n', 'c', 't',
      's', 'p', 'a', 'c', 'e',
      'u', 'n', 'i', 'c', 'o', 'd', 'e',
      'u', 'p', 'p', 'e', 'r',
      'w', 'o', 'r', 'd',
      'x', 'd', 'i', 'g', 'i', 't',
   };

   static const character_pointer_range<charT> ranges[] = 
   {
      {data+0, data+5,}, // alnum
      {data+5, data+10,}, // alpha
      {data+10, data+15,}, // blank
      {data+15, data+20,}, // cntrl
      {data+20, data+21,}, // d
      {data+20, data+25,}, // digit
      {data+25, data+30,}, // graph
      {data+30, data+31,}, // l
      {data+30, data+35,}, // lower
      {data+35, data+40,}, // print
      {data+40, data+45,}, // punct
      {data+45, data+46,}, // s
      {data+45, data+50,}, // space
      {data+57, data+58,}, // u
      {data+50, data+57,}, // unicode
      {data+57, data+62,}, // upper
      {data+62, data+63,}, // w
      {data+62, data+66,}, // word
      {data+66, data+72,}, // xdigit
   };
   static const character_pointer_range<charT>* ranges_begin = ranges;
   static const character_pointer_range<charT>* ranges_end = ranges + (sizeof(ranges)/sizeof(ranges[0]));
   
   character_pointer_range<charT> t = { p1, p2, };
   const character_pointer_range<charT>* p = std::lower_bound(ranges_begin, ranges_end, t);
   if((p != ranges_end) && (t == *p))
      return static_cast<int>(p - ranges);
   return -1;
}

#if 0
//
// parse_value:
// covert a character sequence into a value, return -1 if no digits found:
//
template <class charT, class traits>
int parse_value(const charT*& p1, const charT* p2, const traits& traits_inst, int radix = 10)
{
   return traits_inst.toi(p1, p2, radix);
#if 0
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
#endif
}
#endif

} // re_detail
} // boost

#endif
