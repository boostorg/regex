/*
 *
 * Copyright (c) 1998-2002
 * Dr John Maddock
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Dr John Maddock makes no representations
 * about the suitability of this software for any purpose.  
 * It is provided "as is" without express or implied warranty.
 *
 */
 
 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         match_flags.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares match_flags type.
  */

#ifndef BOOST_REGEX_V4_MATCH_FLAGS
#define BOOST_REGEX_V4_MATCH_FLAGS

#ifdef __cplusplus
#  include <boost/cstdint.hpp>
#endif

#ifdef __cplusplus
namespace boost{
#endif

typedef enum _match_flags
{
   match_default = 0,
   match_not_bol = 1,                                // first is not start of line
   match_not_eol = match_not_bol << 1,               // last is not end of line
   match_not_bob = match_not_eol << 1,               // first is not start of buffer
   match_not_eob = match_not_bob << 1,               // last is not end of buffer
   match_not_bow = match_not_eob << 1,               // first is not start of word
   match_not_eow = match_not_bow << 1,               // last is not end of word
   match_not_dot_newline = match_not_eow << 1,       // \n is not matched by '.'
   match_not_dot_null = match_not_dot_newline << 1,  // '\0' is not matched by '.'
   match_prev_avail = match_not_dot_null << 1,       // *--first is a valid expression
   match_init = match_prev_avail << 1,               // internal use
   match_any = match_init << 1,                      // don't care what we match
   match_not_null = match_any << 1,                  // string can't be null
   match_continuous = match_not_null << 1,           // each grep match must continue from
                                                     // uninterupted from the previous one
   match_partial = match_continuous << 1,            // find partial matches
   
   match_stop = match_partial << 1,                  // stop after first match (grep)
   match_all = match_stop << 1,                      // must find the whole of input even if match_any is set
   match_perl = match_all << 1,                      // Use perl matching rules
   match_posix = match_perl << 1,                    // Use POSIX matching rules
   match_max = match_posix,

   format_all = 0,                                   // enable all extentions to sytax
   format_sed = match_max << 1,                      // sed style replacement.
   format_perl = format_sed << 1,                    // perl style replacement.
   format_no_copy = format_perl << 1,                // don't copy non-matching segments.
   format_first_only = format_no_copy << 1,          // Only replace first occurance.
   format_is_if = format_first_only << 1             // internal use only.

} match_flags;

#if defined(BOOST_MSVC) && (BOOST_MSVC <= 1200)
typedef unsigned long match_flag_type;
} // namespace boost
#else
typedef match_flags match_flag_type;


#ifdef __cplusplus
inline match_flags operator&(match_flags m1, match_flags m2)
{ return static_cast<match_flags>(static_cast<boost::int32_t>(m1) & static_cast<boost::int32_t>(m2)); }
inline match_flags operator|(match_flags m1, match_flags m2)
{ return static_cast<match_flags>(static_cast<boost::int32_t>(m1) | static_cast<boost::int32_t>(m2)); }
inline match_flags operator^(match_flags m1, match_flags m2)
{ return static_cast<match_flags>(static_cast<boost::int32_t>(m1) ^ static_cast<boost::int32_t>(m2)); }
inline match_flags operator~(match_flags m1)
{ return static_cast<match_flags>(~static_cast<boost::int32_t>(m1)); }
inline match_flags& operator&=(match_flags& m1, match_flags m2)
{ m1 = m1&m2; return m1; }
inline match_flags& operator|=(match_flags& m1, match_flags m2)
{ m1 = m1|m2; return m1; }
inline match_flags& operator^=(match_flags& m1, match_flags m2)
{ m1 = m1^m2; return m1; }


} // namespace boost
#endif // __cplusplus
#endif // BOOST_MSVC

#endif
