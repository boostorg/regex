/*
 *
 * Copyright (c) 2003
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
  *   FILE         escape_syntax_type.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares regular expression escape synatx type enumerator.
  */

#ifndef BOOST_REGEX_ERROR_TYPE_HPP
#define BOOST_REGEX_ERROR_TYPE_HPP

#ifdef __cplusplus
namespace boost{
#endif

#ifdef __cplusplus
namespace regex_constants{

typedef unsigned error_type;

static const error_type error_ok = 0;         // not used
static const error_type error_no_match = 1;   // not used
static const error_type error_bad_pattern = 2;
static const error_type error_collate = 3;
static const error_type error_ctype = 4;
static const error_type error_escape = 5;
static const error_type error_subreg = 6;
static const error_type error_brack = 7;
static const error_type error_paren = 8;
static const error_type error_brace = 9;
static const error_type error_badbrace = 10;
static const error_type error_range = 11;
static const error_type error_space = 12;
static const error_type error_badrepeat = 13;
static const error_type error_end = 14;    // not used
static const error_type error_size = 15;
static const error_type error_right_paren = 16;  // not used
static const error_type error_empty = 17;
static const error_type error_complexity = 18;
static const error_type error_stack = 19;
static const error_type error_unknown = 20;

}
}
#endif // __cplusplus

#endif
