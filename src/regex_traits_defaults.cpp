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
  *   FILE         regex_traits_defaults.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares API's for access to regex_traits default properties.
  */

#include <boost/regex/regex_traits.hpp>

namespace boost{ namespace re_detail{

const char* get_default_syntax(regex_constants::syntax_type n)
{
   // if the user hasn't supplied a message catalog, then this supplies
   // default "messages" for us to load in the range 1-100.
   const char* messages[] = {
         "",
         "(",
         ")",
         "$",
         "^",
         ".",
         "*",
         "+",
         "?",
         "[",
         "]",
         "|",
         "\\",
         "#",
         "-",
         "{",
         "}",
         "0123456789",
         "b",
         "B",
         "<",
         ">",
         "",
         "",
         "A`",
         "z'",
         "\n",
         ",",
         "a",
         "f",
         "n",
         "r",
         "t",
         "v",
         "x",
         "c",
         ":",
         "=",
         "e",
         "",
         "",
         "",
         "",
         "",
         "",
         "",
         "",
         "E",
         "Q",
         "X",
         "C",
         "Z",
         "G"
         "!", };

   return ((n >= (sizeof(messages) / sizeof(messages[1]))) ? "" : messages[n]);
}

const char* get_default_error_string(regex_constants::error_type n)
{
   static const char* const s_default_error_messages[] = {
      "Success",             /* REG_NOERROR */
      "No match",             /* REG_NOMATCH */
      "Invalid regular expression",    /* REG_BADPAT */
      "Invalid collation character",      /* REG_ECOLLATE */
      "Invalid character class name",     /* REG_ECTYPE */
      "Trailing backslash",         /* REG_EESCAPE */
      "Invalid back reference",        /* REG_ESUBREG */
      "Unmatched [ or [^",       /* REG_EBRACK */
      "Unmatched ( or \\(",         /* REG_EPAREN */
      "Unmatched { or \\{",           /* REG_EBRACE */
      "Invalid content of \\{\\}",     /* REG_BADBR */
      "Invalid range end",       /* REG_ERANGE */
      "Memory exhausted",           /* REG_ESPACE */
      "Invalid preceding regular expression",   /* REG_BADRPT */
      "Premature end of regular expression", /* REG_EEND */
      "Regular expression too big",    /* REG_ESIZE */
      "Unmatched ) or \\)",         /* REG_ERPAREN */
      "Empty expression",           /* REG_EMPTY */
      "Complexity requirements exceeded",  /* REG_ECOMPLEXITY */
      "Out of stack space", /* REG_ESTACK */
      "Unknown error",    /* REG_E_UNKNOWN */
      "",
      "",
      "",
   };

   return (n > REG_E_UNKNOWN) ? s_default_error_messages[REG_E_UNKNOWN] : s_default_error_messages[n];
}

bool is_combining_implementation(boost::uint_least16_t c)
{
   const boost::uint_least16_t combining_ranges[] = { 0x0300, 0x0361, 
                           0x0483, 0x0486, 
                           0x0903, 0x0903, 
                           0x093E, 0x0940, 
                           0x0949, 0x094C,
                           0x0982, 0x0983,
                           0x09BE, 0x09C0,
                           0x09C7, 0x09CC,
                           0x09D7, 0x09D7,
                           0x0A3E, 0x0A40,
                           0x0A83, 0x0A83,
                           0x0ABE, 0x0AC0,
                           0x0AC9, 0x0ACC,
                           0x0B02, 0x0B03,
                           0x0B3E, 0x0B3E,
                           0x0B40, 0x0B40,
                           0x0B47, 0x0B4C,
                           0x0B57, 0x0B57,
                           0x0B83, 0x0B83,
                           0x0BBE, 0x0BBF,
                           0x0BC1, 0x0BCC,
                           0x0BD7, 0x0BD7,
                           0x0C01, 0x0C03,
                           0x0C41, 0x0C44,
                           0x0C82, 0x0C83,
                           0x0CBE, 0x0CBE,
                           0x0CC0, 0x0CC4,
                           0x0CC7, 0x0CCB,
                           0x0CD5, 0x0CD6,
                           0x0D02, 0x0D03,
                           0x0D3E, 0x0D40,
                           0x0D46, 0x0D4C,
                           0x0D57, 0x0D57,
                           0x0F7F, 0x0F7F,
                           0x20D0, 0x20E1, 
                           0x3099, 0x309A,
                           0xFE20, 0xFE23, 
                           0xffff, 0xffff, };

      const boost::uint_least16_t* p = combining_ranges + 1;
   while(*p < c) p += 2;
   --p;
   if((c >= *p) && (c <= *(p+1)))
         return true;
   return false;
}

} // re_detail
} // boost
