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

namespace boost{

//
// start with the POSIX API versions of these:
//
typedef unsigned reg_error_t;

static const reg_error_t REG_NOERROR = 0;   /* Success.  */
static const reg_error_t REG_NOMATCH = 1;   /* Didn't find a match (for regexec).  */

  /* POSIX regcomp return error codes.  (In the order listed in the
     standard.)  */
static const reg_error_t REG_BADPAT = 2;    /* Invalid pattern.  */
static const reg_error_t REG_ECOLLATE = 3;  /* Undefined collating element.  */
static const reg_error_t REG_ECTYPE = 4;    /* Invalid character class name.  */
static const reg_error_t REG_EESCAPE = 5;   /* Trailing backslash.  */
static const reg_error_t REG_ESUBREG = 6;   /* Invalid back reference.  */
static const reg_error_t REG_EBRACK = 7;    /* Unmatched left bracket.  */
static const reg_error_t REG_EPAREN = 8;    /* Parenthesis imbalance.  */
static const reg_error_t REG_EBRACE = 9;    /* Unmatched \{.  */
static const reg_error_t REG_BADBR = 10;    /* Invalid contents of \{\}.  */
static const reg_error_t REG_ERANGE = 11;   /* Invalid range end.  */
static const reg_error_t REG_ESPACE = 12;   /* Ran out of memory.  */
static const reg_error_t REG_BADRPT = 13;   /* No preceding re for repetition op.  */
static const reg_error_t REG_EEND = 14;     /* unexpected end of expression */
static const reg_error_t REG_ESIZE = 15;    /* expression too big */
static const reg_error_t REG_ERPAREN = REG_EPAREN;   /* unmatched right parenthesis */
static const reg_error_t REG_EMPTY = 17;    /* empty expression */
static const reg_error_t REG_E_MEMORY = REG_ESIZE; /* out of memory */
static const reg_error_t REG_ECOMPLEXITY = 18; /* complexity too high */
static const reg_error_t REG_ESTACK = 19;   /* out of stack space */
static const reg_error_t REG_E_UNKNOWN = 20; /* unknown error */
static const reg_error_t REG_ENOSYS = REG_E_UNKNOWN; /* Reserved. */

namespace regex_constants{

typedef ::boost::reg_error_t error_type;

static const error_type error_collate = REG_ECOLLATE;
static const error_type error_ctype = REG_ECTYPE;
static const error_type error_escape = REG_EESCAPE;
static const error_type error_subreg = REG_ESUBREG;
static const error_type error_brack = REG_EBRACK;
static const error_type error_paren = REG_EPAREN;
static const error_type error_brace = REG_EBRACE;
static const error_type error_badbrace = REG_BADBR;
static const error_type error_range = REG_ERANGE;
static const error_type error_space = REG_ESPACE;
static const error_type error_badrepeat = REG_BADRPT;
static const error_type error_size = REG_ESIZE;
static const error_type error_empty = REG_EMPTY;
static const error_type error_complexity = REG_ECOMPLEXITY;
static const error_type error_stack = REG_ESTACK;
static const error_type error_unknown = REG_E_UNKNOWN;

}
}

#endif
