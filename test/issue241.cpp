// Copyright 2026 Treston Cuzzort.
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or https://www.boost.org/LICENSE_1_0.txt.

#include <boost/core/lightweight_test.hpp>
#include <boost/regex.hpp>
#include <string>

// The mask for word is independent of the masks for its constituent classes.
// Bitwise AND cannot be used to find the intersection of these classes.
template <class CharT>
struct independent_traits : boost::regex_traits<CharT>
{
   typedef unsigned char char_class_type;

   template <class Iterator>
   char_class_type lookup_classname(Iterator first, Iterator last) const
   {
      std::string name;
      for(; first != last; ++first)
      {
         char c = static_cast<char>(*first);
         name += (c >= 'A' && c <= 'Z') ? static_cast<char>(c - 'A' + 'a') : c;
      }
      if(name == "w" || name == "word") return 1;
      if(name == "d" || name == "digit") return 2;
      if(name == "s" || name == "space") return 4;
      if(name == "alpha") return 8;
      if(name == "l" || name == "lower") return 16;
      if(name == "u" || name == "upper") return 32;
      return 0;
   }

   bool isctype(CharT c, char_class_type mask) const
   {
      const unsigned int value = static_cast<unsigned int>(c);
      const bool lower = (c >= 'a' && c <= 'z') || value == 0x101;
      const bool upper = (c >= 'A' && c <= 'Z') || value == 0x100;
      const bool digit = (c >= '0' && c <= '9') || value == 0x660;
      const bool space = c == ' ' || c == '\t' || c == '\n';
      return ((mask & 1) && (lower || upper || digit || c == '_'))
         || ((mask & 2) && digit) || ((mask & 4) && space)
         || ((mask & 8) && (lower || upper))
         || ((mask & 16) && lower) || ((mask & 32) && upper);
   }
};

template <class CharT>
std::basic_string<CharT> widen(const char* source)
{
   std::basic_string<CharT> result;
   while(*source) result += static_cast<CharT>(*source++);
   return result;
}

struct set_case
{
   const char* expression;
   const char* positive;
   const char* negative;
   bool negate;
   bool extra;
};

template <class CharT, class Traits>
void test_sets()
{
   const set_case cases[] = {
      {"[\\W\\D]", "", "wd", false, false},
      {"[\\D\\W]", "", "dw", false, false},
      {"[\\W\\D\\W]", "", "wdw", false, false},
      {"[\\W\\D\\S]", "", "wds", false, false},
      {"[\\W\\W]", "", "ww", false, false},
      {"[\\W]", "", "w", false, false},
      {"[\\W\\d]", "d", "w", false, false},
      {"[\\D\\w]", "w", "d", false, false},
      {"[\\W\\D\\d]", "d", "wd", false, false},
      {"[^\\W\\D]", "", "wd", true, false},
      {"[^\\W\\D\\S]", "", "wds", true, false},
      {"[\\W\\D0x-z]", "", "wd", false, true},
      {"[^\\W\\D0x-z]", "", "wd", true, true},
      {"[\\D0x-z]", "", "d", false, true},
      {"[\\W\\D\\S0x-z]", "", "wds", false, true}
   };
   Traits traits;
   for(const set_case& item : cases)
   {
      const std::basic_string<CharT> expression = widen<CharT>(item.expression);
      const boost::basic_regex<CharT, Traits> re(expression);
      const boost::basic_regex<CharT, Traits> repeated(expression + widen<CharT>("+"));
      const unsigned int extra[] = {0x100, 0x101, 0x660, 0x2603};
      const unsigned int count = 256 + (sizeof(CharT) > 1 ? 4 : 0);
      for(unsigned int index = 0; index < count; ++index)
      {
         const CharT c = static_cast<CharT>(index < 256 ? index : extra[index - 256]);
         bool expected = item.extra && (c == '0' || (c >= 'x' && c <= 'z'));
         for(const char* p = item.positive; *p; ++p)
         {
            const CharT name = static_cast<CharT>(*p);
            expected = expected || traits.isctype(c, traits.lookup_classname(&name, &name + 1));
         }
         for(const char* p = item.negative; *p; ++p)
         {
            const CharT name = static_cast<CharT>(*p);
            expected = expected || !traits.isctype(c, traits.lookup_classname(&name, &name + 1));
         }
         if(item.negate) expected = !expected;
         const std::basic_string<CharT> text(1, c);
         BOOST_TEST_EQ(boost::regex_match(text, re), expected);
         BOOST_TEST_EQ(boost::regex_search(text, re), expected);
         BOOST_TEST_EQ(boost::regex_match(std::basic_string<CharT>(3, c), repeated), expected);
      }
   }
   const boost::basic_regex<CharT, Traits> insensitive(
      widen<CharT>("[[:^lower:][:^upper:]]"), boost::regex::icase);
   BOOST_TEST(!boost::regex_match(widen<CharT>("a"), insensitive));
   BOOST_TEST(!boost::regex_match(widen<CharT>("A"), insensitive));
   BOOST_TEST(boost::regex_match(widen<CharT>("0"), insensitive));
   const boost::basic_regex<CharT, Traits> equivalent(widen<CharT>("[\\W\\D[=0=]]"));
   BOOST_TEST(boost::regex_match(widen<CharT>("0"), equivalent));
   BOOST_TEST(boost::regex_match(widen<CharT>("a"), equivalent));
   BOOST_TEST(!boost::regex_match(widen<CharT>("1"), equivalent));
}

int main()
{
   test_sets<char, boost::regex_traits<char> >();
   test_sets<char, independent_traits<char> >();
#ifndef BOOST_NO_WREGEX
   test_sets<wchar_t, boost::regex_traits<wchar_t> >();
   test_sets<wchar_t, independent_traits<wchar_t> >();
#endif
   return boost::report_errors();
}
