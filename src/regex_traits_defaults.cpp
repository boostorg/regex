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

#define BOOST_REGEX_SOURCE
#include <boost/regex/regex_traits.hpp>

namespace boost{ namespace re_detail{

BOOST_REGEX_DECL const char* BOOST_REGEX_CALL get_default_syntax(regex_constants::syntax_type n)
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
         "G",
         "!", };

   return ((n >= (sizeof(messages) / sizeof(messages[1]))) ? "" : messages[n]);
}

BOOST_REGEX_DECL const char* BOOST_REGEX_CALL get_default_error_string(regex_constants::error_type n)
{
   static const char* const s_default_error_messages[] = {
      "Success",             /* REG_NOERROR */
      "No match",             /* REG_NOMATCH */
      "Invalid regular expression",    /* REG_BADPAT */
      "Invalid collation character",      /* REG_ECOLLATE */
      "Invalid character class name",     /* REG_ECTYPE */
      "Invalid or trailing backslash",         /* REG_EESCAPE */
      "Invalid back reference",        /* REG_ESUBREG */
      "Unmatched [ or [^",       /* REG_EBRACK */
      "Unmatched ( or \\(",         /* REG_EPAREN */
      "Unmatched { or \\{",           /* REG_EBRACE */
      "Invalid content of repeat range",     /* REG_BADBR */
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

BOOST_REGEX_DECL bool BOOST_REGEX_CALL is_combining_implementation(boost::uint_least16_t c)
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

//
// these are the POSIX collating names:
//
BOOST_REGEX_DECL const char* def_coll_names[] = {
"NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "alert", "backspace", "tab", "newline", 
"vertical-tab", "form-feed", "carriage-return", "SO", "SI", "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", 
"SYN", "ETB", "CAN", "EM", "SUB", "ESC", "IS4", "IS3", "IS2", "IS1", "space", "exclamation-mark", 
"quotation-mark", "number-sign", "dollar-sign", "percent-sign", "ampersand", "apostrophe", 
"left-parenthesis", "right-parenthesis", "asterisk", "plus-sign", "comma", "hyphen", 
"period", "slash", "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", 
"colon", "semicolon", "less-than-sign", "equals-sign", "greater-than-sign", 
"question-mark", "commercial-at", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", 
"Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "left-square-bracket", "backslash", 
"right-square-bracket", "circumflex", "underscore", "grave-accent", "a", "b", "c", "d", "e", "f", 
"g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "left-curly-bracket", 
"vertical-line", "right-curly-bracket", "tilde", "DEL", "", 
};

// these multi-character collating elements
// should keep most Western-European locales
// happy - we should really localise these a
// little more - but this will have to do for
// now:

BOOST_REGEX_DECL const char* def_multi_coll[] = {
   "ae",
   "Ae",
   "AE",
   "ch",
   "Ch",
   "CH",
   "ll",
   "Ll",
   "LL",
   "ss",
   "Ss",
   "SS",
   "nj",
   "Nj",
   "NJ",
   "dz",
   "Dz",
   "DZ",
   "lj",
   "Lj",
   "LJ",
   "",
};



BOOST_REGEX_DECL std::string BOOST_REGEX_CALL lookup_default_collate_name(const std::string& name)
{
   unsigned int i = 0;
   while(*def_coll_names[i])
   {
      if(def_coll_names[i] == name)
      {
         return std::string(1, char(i));
      }
      ++i;
   }
   i = 0;
   while(*def_multi_coll[i])
   {
      if(def_multi_coll[i] == name)
      {
         return def_multi_coll[i];
      }
      ++i;
   }
   return std::string();
}


} // re_detail
} // boost
