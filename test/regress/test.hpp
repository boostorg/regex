

#ifndef BOOST_REGEX_REGRESS_TEST_HPP
#define BOOST_REGEX_REGRESS_TEST_HPP
#include "test_not_regex.hpp"
#include "test_regex_search.hpp"


//
// define test entry proc, this forwards on to the appropriate
// real test:
//
template <class charT, class tagT>
void test(const charT&, const tagT& tag)
{
   boost::basic_regex<charT> e;
   test(e, tag);
}

//
// define function to pack args into an array:
//
const int* make_array(int first, ...);


//
// define macros for testing invalid regexes:
//
#define TEST_INVALID_REGEX_N(s, f)\
   do{\
      const char e[] = { s };\
      std::string se(e, sizeof(e) - 1);\
      test_info<char>::set_info(__FILE__, __LINE__, se, f);\
      test(char(0), test_invalid_regex_tag());\
   }while(0)

#ifndef BOOST_NO_WREGEX
#define TEST_INVALID_REGEX_W(s, f)\
   do{\
      const wchar_t e[] = { s };\
      std::wstring se(e, (sizeof(e) / sizeof(wchar_t)) - 1);\
      test_info<wchar_t>::set_info(__FILE__, __LINE__, se, f);\
      test(wchar_t(0), test_invalid_regex_tag());\
   }while(0)
#else
#define TEST_INVALID_REGEX_W(s, f)
#endif

#define TEST_INVALID_REGEX(s, f)\
   TEST_INVALID_REGEX_N(s, f);\
   TEST_INVALID_REGEX_W(BOOST_JOIN(L, s), f)

//
// define macros for testing regex searches:
//
#define TEST_REGEX_SEARCH_N(s, f, t, m, a)\
   do{\
      const char e[] = { s };\
      std::string se(e, sizeof(e) - 1);\
      const char st[] = { t };\
      std::string sst(st, sizeof(st) - 1);\
      test_info<char>::set_info(__FILE__, __LINE__, se, f, sst, m, a);\
      test(char(0), test_regex_search_tag());\
   }while(0)

#ifndef BOOST_NO_WREGEX
#define TEST_REGEX_SEARCH_W(s, f, t, m, a)\
   do{\
      const wchar_t e[] = { s };\
      std::wstring se(e, (sizeof(e) / sizeof(wchar_t)) - 1);\
      const wchar_t st[] = { t };\
      std::wstring sst(st, (sizeof(st) / sizeof(wchar_t)) - 1);\
      test_info<wchar_t>::set_info(__FILE__, __LINE__, se, f, sst, m, a);\
      test(wchar_t(0), test_regex_search_tag());\
   }while(0)
#else
#define TEST_REGEX_SEARCH_W(s, f, t, m, a)
#endif

#define TEST_REGEX_SEARCH(s, f, t, m, a)\
   TEST_REGEX_SEARCH_N(s, f, t, m, a);\
   TEST_REGEX_SEARCH_W(BOOST_JOIN(L, s), f, BOOST_JOIN(L, t), m, a)

//
// define the test group proceedures:
//
void basic_tests();
void test_alt();
void test_sets();
void test_anchors();
void test_backrefs();
void test_character_escapes();
void test_assertion_escapes();
void test_tricky_cases();


#endif
