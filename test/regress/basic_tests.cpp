
#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, < 0x560)
// we get unresolved externals from basic_string
// unless we do this, a well known Borland bug:
#define _RWSTD_COMPILE_INSTANTIATE
#endif

#include "test.hpp"

#ifdef BOOST_MSVC
#pragma warning(disable:4127)
#endif

void basic_tests()
{
   using namespace boost::regex_constants;
   TEST_REGEX_SEARCH("a", basic, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("a", basic, "bba", match_default, make_array(2, 3, -2, -2));
   TEST_REGEX_SEARCH("Z", perl, "aaa", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("Z", perl, "xxxxZZxxx", match_default, make_array(4, 5, -2, 5, 6, -2, -2));
   // and some simple brackets:
   TEST_REGEX_SEARCH("(a)", perl, "zzzaazz", match_default, make_array(3, 4, 3, 4, -2, 4, 5, 4, 5, -2, -2));
   TEST_REGEX_SEARCH("()", perl, "zzz", match_default, make_array(0, 0, 0, 0, -2, 1, 1, 1, 1, -2, 2, 2, 2, 2, -2, 3, 3, 3, 3, -2, -2));
   TEST_REGEX_SEARCH("()", perl, "", match_default, make_array(0, 0, 0, 0, -2, -2));
   TEST_INVALID_REGEX("(", perl);
   TEST_INVALID_REGEX(")", perl);
   TEST_INVALID_REGEX("(aa", perl);
   TEST_INVALID_REGEX("aa)", perl);
   TEST_REGEX_SEARCH("a", perl, "b", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("\\(\\)", perl, "()", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("\\(a\\)", perl, "(a)", match_default, make_array(0, 3, -2, -2));
   TEST_INVALID_REGEX("\\()", perl);
   TEST_INVALID_REGEX("(\\)", perl);
   TEST_REGEX_SEARCH("p(a)rameter", perl, "ABCparameterXYZ", match_default, make_array(3, 12, 4, 5, -2, -2));
   TEST_REGEX_SEARCH("[pq](a)rameter", perl, "ABCparameterXYZ", match_default, make_array(3, 12, 4, 5, -2, -2));

   // now try escaped brackets:
   TEST_REGEX_SEARCH("\\(a\\)", basic, "zzzaazz", match_default, make_array(3, 4, 3, 4, -2, 4, 5, 4, 5, -2, -2));
   TEST_REGEX_SEARCH("\\(\\)", basic, "zzz", match_default, make_array(0, 0, 0, 0, -2, 1, 1, 1, 1, -2, 2, 2, 2, 2, -2, 3, 3, 3, 3, -2, -2));
   TEST_REGEX_SEARCH("\\(\\)", basic, "", match_default, make_array(0, 0, 0, 0, -2, -2));
   TEST_INVALID_REGEX("\\(", basic);
   TEST_INVALID_REGEX("\\)", basic);
   TEST_INVALID_REGEX("\\(aa", basic);
   TEST_INVALID_REGEX("aa\\)", basic);
   TEST_REGEX_SEARCH("()", basic, "()", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("(a)", basic, "(a)", match_default, make_array(0, 3, -2, -2));
   TEST_INVALID_REGEX("\\()", basic);
   TEST_INVALID_REGEX("(\\)", basic);
   TEST_REGEX_SEARCH("p\\(a\\)rameter", basic, "ABCparameterXYZ", match_default, make_array(3, 12, 4, 5, -2, -2));
   TEST_REGEX_SEARCH("[pq]\\(a\\)rameter", basic, "ABCparameterXYZ", match_default, make_array(3, 12, 4, 5, -2, -2));

   // now move on to "." wildcards
   TEST_REGEX_SEARCH(".", perl, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH(".", perl, "\n", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH(".", perl, "\r", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH(".", perl, "\0", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH(".", perl, "a", match_not_dot_newline, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH(".", perl, "\n", match_not_dot_newline, make_array(-2, -2));
   TEST_REGEX_SEARCH(".", perl, "\r", match_not_dot_newline, make_array(-2, -2));
   TEST_REGEX_SEARCH(".", perl, "\0", match_not_dot_newline, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH(".", perl, "\n", match_not_dot_null | match_not_dot_newline, make_array(-2, -2));
   TEST_REGEX_SEARCH(".", perl, "\r", match_not_dot_null | match_not_dot_newline, make_array(-2, -2));
   TEST_REGEX_SEARCH(".", perl, "\0", match_not_dot_null | match_not_dot_newline, make_array(-2, -2));
   TEST_REGEX_SEARCH(".", basic, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH(".", basic, "\n", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH(".", basic, "\r", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH(".", basic, "\0", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH(".", basic, "a", match_not_dot_newline, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH(".", basic, "\n", match_not_dot_newline, make_array(-2, -2));
   TEST_REGEX_SEARCH(".", basic, "\r", match_not_dot_newline, make_array(-2, -2));
   TEST_REGEX_SEARCH(".", basic, "\0", match_not_dot_newline, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH(".", basic, "\n", match_not_dot_null | match_not_dot_newline, make_array(-2, -2));
   TEST_REGEX_SEARCH(".", basic, "\r", match_not_dot_null | match_not_dot_newline, make_array(-2, -2));
   TEST_REGEX_SEARCH(".", basic, "\0", match_not_dot_null | match_not_dot_newline, make_array(-2, -2));

   // simple repeats:
   TEST_REGEX_SEARCH("a*", perl, "b", match_default, make_array(0, 0, -2, 1, 1, -2, -2));
   TEST_REGEX_SEARCH("ab*", perl, "ab", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("ab*", perl, "sssabbbbbbsss", match_default, make_array(3, 10, -2, -2));
   TEST_REGEX_SEARCH("ab*c*", perl, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("ab*c*", perl, "abbb", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab*c*", perl, "accc", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab*c*", perl, "abbcc", match_default, make_array(0, 5, -2, -2));
   TEST_INVALID_REGEX("*a", perl);
   TEST_INVALID_REGEX("\\<*", perl);
   TEST_INVALID_REGEX("\\>*", perl);
   TEST_REGEX_SEARCH("\n*", perl, "\n\n", match_default, make_array(0, 2, -2, 2, 2, -2, -2));
   TEST_REGEX_SEARCH("\\**", perl, "**", match_default, make_array(0, 2, -2, 2, 2, -2, -2));
   TEST_REGEX_SEARCH("\\*", perl, "*", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("(ab)*", perl, "abab", match_default, make_array(0, 4, 2, 4, -2, 4, 4, -2, -2));

   // now try operator + :
   TEST_REGEX_SEARCH("ab+", perl, "a", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab+", perl, "ab", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("ab+", perl, "sssabbbbbbsss", match_default, make_array(3, 10, -2, -2));
   TEST_REGEX_SEARCH("ab+c+", perl, "abbb", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab+c+", perl, "accc", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab+c+", perl, "abbcc", match_default, make_array(0, 5, -2, -2));
   TEST_INVALID_REGEX("+a", perl);
   TEST_INVALID_REGEX("\\<+", perl);
   TEST_INVALID_REGEX("\\>+", perl);
   TEST_REGEX_SEARCH("\n+", perl, "\n\n", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("\\+", perl, "+", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\+", perl, "++", match_default, make_array(0, 1, -2, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("\\++", perl, "++", match_default, make_array(0, 2, -2, -2));

   TEST_REGEX_SEARCH("+", basic|bk_plus_qm, "+", match_default, make_array(0, 1, -2, -2));
   TEST_INVALID_REGEX("\\+", basic|bk_plus_qm);
   TEST_REGEX_SEARCH("a\\+", basic|bk_plus_qm, "aa", match_default, make_array(0, 2, -2, -2));

   // now try operator ?
   TEST_REGEX_SEARCH("a?", perl, "b", match_default, make_array(0, 0, -2, 1, 1, -2, -2));
   TEST_REGEX_SEARCH("ab?", perl, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("ab?", perl, "ab", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("ab?", perl, "sssabbbbbbsss", match_default, make_array(3, 5, -2, -2));
   TEST_REGEX_SEARCH("ab?c?", perl, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("ab?c?", perl, "abbb", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("ab?c?", perl, "accc", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("ab?c?", perl, "abcc", match_default, make_array(0, 3, -2, -2));
   TEST_INVALID_REGEX("?a", perl);
   TEST_INVALID_REGEX("\\<?", perl);
   TEST_INVALID_REGEX("\\>?", perl);
   TEST_REGEX_SEARCH("\n?", perl, "\n\n", match_default, make_array(0, 1, -2, 1, 2, -2, 2, 2, -2, -2));
   TEST_REGEX_SEARCH("\\?", perl, "?", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\?", perl, "?", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\??", perl, "??", match_default, make_array(0, 1, -2, 1, 2, -2, 2, 2, -2, -2));
   TEST_REGEX_SEARCH("?", basic|bk_plus_qm, "?", match_default, make_array(0, 1, -2, -2));
   TEST_INVALID_REGEX("\\?", basic|bk_plus_qm);
   TEST_REGEX_SEARCH("a\\?", basic|bk_plus_qm, "aa", match_default, make_array(0, 1, -2, 1, 2, -2, 2, 2, -2, -2));
   TEST_REGEX_SEARCH("a\\?", basic|bk_plus_qm, "b", match_default, make_array(0, 0, -2, 1, 1, -2, -2));

   TEST_REGEX_SEARCH("a?", basic, "a?", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a+", basic, "a+", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a\\?", basic, "a?", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a\\+", basic, "a+", match_default, make_array(0, 2, -2, -2));

   // now try operator {}
   TEST_REGEX_SEARCH("a{2}", perl, "a", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("a{2}", perl, "aa", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a{2}", perl, "aaa", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a{2,}", perl, "a", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("a{2,}", perl, "aa", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a{2,}", perl, "aaaaa", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("a{2,4}", perl, "a", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("a{2,4}", perl, "aa", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a{2,4}", perl, "aaa", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a{2,4}", perl, "aaaa", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("a{2,4}", perl, "aaaaa", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("a{ 2 , 4 }", perl, "aaaaa", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("a{ 2 , }", perl, "aaaaa", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("a{ 2 }", perl, "aaa", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a\\{\\}", perl, "a{}", match_default, make_array(0, 3, -2, -2));
   TEST_INVALID_REGEX("a{}", perl);
   TEST_INVALID_REGEX("a{", perl);
   TEST_INVALID_REGEX("a{1", perl);
   TEST_INVALID_REGEX("a{1,", perl);
   TEST_INVALID_REGEX("a{ }", perl);
   TEST_INVALID_REGEX("a}", perl);
   TEST_INVALID_REGEX("{1}", perl);
   TEST_INVALID_REGEX("a{b}", perl);
   TEST_INVALID_REGEX("a{1b}", perl);
   TEST_INVALID_REGEX("a{1,b}", perl);
   TEST_INVALID_REGEX("a{1,2v}", perl);

   // now try operator \\{\\} for POSIX basic regexes
   TEST_REGEX_SEARCH("a\\{2\\}", basic, "a", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("a\\{2\\}", basic, "aa", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a\\{2\\}", basic, "aaa", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a\\{2,\\}", basic, "a", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("a\\{2,\\}", basic, "aa", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a\\{2,\\}", basic, "aaaaa", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("a\\{2,4\\}", basic, "a", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("a\\{2,4\\}", basic, "aa", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a\\{2,4\\}", basic, "aaa", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a\\{2,4\\}", basic, "aaaa", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("a\\{2,4\\}", basic, "aaaaa", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("a\\{ 2 , 4 \\}", basic, "aaaaa", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("a\\{ 2 , \\}", basic, "aaaaa", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("a\\{ 2 \\}", basic, "aaa", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a{}", basic, "a{}", match_default, make_array(0, 3, -2, -2));
   TEST_INVALID_REGEX("a\\{\\}", basic);
   TEST_INVALID_REGEX("a\\{", basic);
   TEST_INVALID_REGEX("a\\{1", basic);
   TEST_INVALID_REGEX("a\\{1,", basic);
   TEST_INVALID_REGEX("a\\{ \\}", basic);
   TEST_INVALID_REGEX("a\\}", basic);
   TEST_INVALID_REGEX("\\{1\\}", basic);
   TEST_INVALID_REGEX("a\\{b\\}", basic);
   TEST_INVALID_REGEX("a\\{1b\\}", basic);
   TEST_INVALID_REGEX("a\\{1,b\\}", basic);
   TEST_INVALID_REGEX("a\\{1,2v\\}", basic);

}

void test_alt()
{
   using namespace boost::regex_constants;
   // now test the alternation operator |
   TEST_REGEX_SEARCH("a|b", perl, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("a|b", perl, "b", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("a|b|c", perl, "c", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("a|(b)|.", perl, "b", match_default, make_array(0, 1, 0, 1, -2, -2));
   TEST_REGEX_SEARCH("(a)|b|.", perl, "a", match_default, make_array(0, 1, 0, 1, -2, -2));
   TEST_REGEX_SEARCH("a(b|c)", perl, "ab", match_default, make_array(0, 2, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("a(b|c)", perl, "ac", match_default, make_array(0, 2, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("a(b|c)", perl, "ad", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("(a|b|c)", perl, "c", match_default, make_array(0, 1, 0, 1, -2, -2));
   TEST_REGEX_SEARCH("(a|(b)|.)", perl, "b", match_default, make_array(0, 1, 0, 1, 0, 1, -2, -2));
   TEST_INVALID_REGEX("|c", perl);
   TEST_INVALID_REGEX("c|", perl);
   TEST_INVALID_REGEX("(|)", perl);
   TEST_INVALID_REGEX("(a|)", perl);
   TEST_INVALID_REGEX("(|a)", perl);
   TEST_REGEX_SEARCH("a\\|", perl, "a|", match_default, make_array(0, 2, -2, -2));

   TEST_REGEX_SEARCH("a|", basic, "a|", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a\\|", basic, "a|", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("|", basic, "|", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("a|", basic|bk_vbar, "a|", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a\\|b", basic|bk_vbar, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("a\\|b", basic|bk_vbar, "b", match_default, make_array(0, 1, -2, -2));
}

void test_sets()
{
   using namespace boost::regex_constants;
   // now test the set operator []
   TEST_REGEX_SEARCH("[abc]", extended, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[abc]", extended, "b", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[abc]", extended, "c", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[abc]", extended, "d", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("[^bcd]", extended, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[^bcd]", extended, "b", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("[^bcd]", extended, "d", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("[^bcd]", extended, "e", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("a[b]c", extended, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a[ab]c", extended, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a[^ab]c", extended, "adc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a[]b]c", extended, "a]c", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a[[b]c", extended, "a[c", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a[-b]c", extended, "a-c", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a[^]b]c", extended, "adc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a[^-b]c", extended, "adc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a[b-]c", extended, "a-c", match_default, make_array(0, 3, -2, -2));
   TEST_INVALID_REGEX("a[b", extended);
   TEST_INVALID_REGEX("a[]", extended);

   // now some ranges:
   TEST_REGEX_SEARCH("[b-e]", extended, "a", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("[b-e]", extended, "b", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[b-e]", extended, "e", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[b-e]", extended, "f", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("[^b-e]", extended, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[^b-e]", extended, "b", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("[^b-e]", extended, "e", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("[^b-e]", extended, "f", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("a[1-3]c", extended, "a2c", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a[-3]c", extended, "a-c", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a[-3]c", extended, "a3c", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a[^-3]c", extended, "a-c", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("a[^-3]c", extended, "a3c", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("a[^-3]c", extended, "axc", match_default, make_array(0, 3, -2, -2));
   TEST_INVALID_REGEX("a[3-1]c", extended);
   TEST_INVALID_REGEX("a[1-3-5]c", extended);
   TEST_INVALID_REGEX("a[1-", extended);

   // and some classes
   TEST_REGEX_SEARCH("a[[:alpha:]]c", extended, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_INVALID_REGEX("a[[:unknown:]]c", extended);
   TEST_INVALID_REGEX("a[[:", extended);
   TEST_INVALID_REGEX("a[[:alpha", extended);
   TEST_INVALID_REGEX("a[[:alpha:]", extended);
   TEST_INVALID_REGEX("a[[:alpha,:]", extended);
   TEST_INVALID_REGEX("a[[:]:]]b", extended);
   TEST_INVALID_REGEX("a[[:-:]]b", extended);
   TEST_INVALID_REGEX("a[[:alph:]]", extended);
   TEST_INVALID_REGEX("a[[:alphabet:]]", extended);
   TEST_REGEX_SEARCH("[[:alnum:]]+", extended, "-%@a0X_-", match_default, make_array(3, 6, -2, -2));
   TEST_REGEX_SEARCH("[[:alpha:]]+", extended, " -%@aX_0-", match_default, make_array(4, 6, -2, -2));
   TEST_REGEX_SEARCH("[[:blank:]]+", extended, "a  \tb", match_default, make_array(1, 4, -2, -2));
   TEST_REGEX_SEARCH("[[:cntrl:]]+", extended, " a\n\tb", match_default, make_array(2, 4, -2, -2));
   TEST_REGEX_SEARCH("[[:digit:]]+", extended, "a019b", match_default, make_array(1, 4, -2, -2));
   TEST_REGEX_SEARCH("[[:graph:]]+", extended, " a%b ", match_default, make_array(1, 4, -2, -2));
   TEST_REGEX_SEARCH("[[:lower:]]+", extended, "AabC", match_default, make_array(1, 3, -2, -2));
   TEST_REGEX_SEARCH("[[:print:]]+", extended, "AabC", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("[[:punct:]]+", extended, " %-&\t", match_default, make_array(1, 4, -2, -2));
   TEST_REGEX_SEARCH("[[:space:]]+", extended, "a \n\t\rb", match_default, make_array(1, 5, -2, -2));
   TEST_REGEX_SEARCH("[[:upper:]]+", extended, "aBCd", match_default, make_array(1, 3, -2, -2));
   TEST_REGEX_SEARCH("[[:xdigit:]]+", extended, "p0f3Cx", match_default, make_array(1, 5, -2, -2));

   //
   // escapes are supported in character classes if we have either
   // perl or awk regular expressions:
   //
   TEST_REGEX_SEARCH("[\\n]", perl, "\n", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[\\n]", basic, "\n", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("[\\n]", basic, "\\", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[[:class:]", basic|no_char_classes, ":", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[[:class:]", basic|no_char_classes, "[", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[[:class:]", basic|no_char_classes, "c", match_default, make_array(0, 1, -2, -2));
   //
   // test single character escapes:
   //
   TEST_REGEX_SEARCH("\\w", perl, "A", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\w", perl, "Z", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\w", perl, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\w", perl, "z", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\w", perl, "_", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\w", perl, "}", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("\\w", perl, "`", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("\\w", perl, "[", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("\\w", perl, "@", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("\\W", perl, "a", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("\\W", perl, "z", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("\\W", perl, "A", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("\\W", perl, "Z", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("\\W", perl, "_", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("\\W", perl, "}", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\W", perl, "`", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\W", perl, "[", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\W", perl, "@", match_default, make_array(0, 1, -2, -2));

   // collating elements
   TEST_REGEX_SEARCH("[[.zero.]]", perl, "0", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[[.one.]]", perl, "1", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[[.two.]]", perl, "2", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[[.three.]]", perl, "3", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[[.a.]]", perl, "bac", match_default, make_array(1, 2, -2, -2));
   TEST_REGEX_SEARCH("[[.right-curly-bracket.]]", perl, "}", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[[.NUL.]]", perl, "\0", match_default, make_array(0, 1, -2, -2));
   TEST_INVALID_REGEX("[[:<:]z]", perl);
   TEST_INVALID_REGEX("[a[:>:]]", perl);
   TEST_REGEX_SEARCH("[[.A.]]", extended|icase, "A", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[[.A.]]", extended|icase, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[[.A.]-b]+", extended|icase, "AaBb", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("[A-[.b.]]+", extended|icase, "AaBb", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("[[.a.]-B]+", extended|icase, "AaBb", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("[a-[.B.]]+", extended|icase, "AaBb", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("[\x61]", extended, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[\x61-c]+", extended, "abcd", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("[a-\x63]+", extended, "abcd", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("[[.a.]-c]+", extended, "abcd", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("[a-[.c.]]+", extended, "abcd", match_default, make_array(0, 3, -2, -2));
   TEST_INVALID_REGEX("[[:alpha:]-a]", extended);
   TEST_INVALID_REGEX("[a-[:alpha:]]", extended);
   TEST_REGEX_SEARCH("[[.ae.]]", basic, "ae", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("[[.ae.]]", basic, "aE", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("[[.AE.]]", basic, "AE", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("[[.Ae.]]", basic, "Ae", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("[[.ae.]-b]", basic, "a", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("[[.ae.]-b]", basic, "b", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[[.ae.]-b]", basic, "ae", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("[a-[.ae.]]", basic, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[a-[.ae.]]", basic, "b", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("[a-[.ae.]]", basic, "ae", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("[[.ae.]]", basic|icase, "AE", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("[[.ae.]]", basic|icase, "Ae", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("[[.AE.]]", basic|icase, "Ae", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("[[.Ae.]]", basic|icase, "aE", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("[[.AE.]-B]", basic|icase, "a", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("[[.Ae.]-b]", basic|icase, "b", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[[.Ae.]-b]", basic|icase, "B", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[[.ae.]-b]", basic|icase, "AE", match_default, make_array(0, 2, -2, -2));
   //
   // try some equivalence classes:
   //
   TEST_REGEX_SEARCH("[[=a=]]", basic, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[[=a=]]", basic, "A", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("[[=ae=]]", basic, "ae", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("[[=right-curly-bracket=]]", basic, "}", match_default, make_array(0, 1, -2, -2));
   //
   // now some perl style single character classes:
   //
   TEST_REGEX_SEARCH("\\l+", perl, "ABabcAB", match_default, make_array(2, 5, -2, -2));
   TEST_REGEX_SEARCH("[\\l]+", perl, "ABabcAB", match_default, make_array(2, 5, -2, -2));
   TEST_INVALID_REGEX("[\\l-a]", perl);
   TEST_INVALID_REGEX("[\\L]", perl);
   TEST_REGEX_SEARCH("\\L+", perl, "abABCab", match_default, make_array(2, 5, -2, -2));
   TEST_REGEX_SEARCH("\\u+", perl, "abABCab", match_default, make_array(2, 5, -2, -2));
   TEST_REGEX_SEARCH("[\\u]+", perl, "abABCab", match_default, make_array(2, 5, -2, -2));
   TEST_INVALID_REGEX("[\\U]", perl);
   TEST_REGEX_SEARCH("\\U+", perl, "ABabcAB", match_default, make_array(2, 5, -2, -2));
   TEST_REGEX_SEARCH("\\d+", perl, "AB012AB", match_default, make_array(2, 5, -2, -2));
   TEST_REGEX_SEARCH("[\\d]+", perl, "AB012AB", match_default, make_array(2, 5, -2, -2));
   TEST_INVALID_REGEX("[\\D]", perl);
   TEST_REGEX_SEARCH("\\D+", perl, "01abc01", match_default, make_array(2, 5, -2, -2));
   TEST_REGEX_SEARCH("\\s+", perl, "AB   AB", match_default, make_array(2, 5, -2, -2));
   TEST_REGEX_SEARCH("[\\s]+", perl, "AB   AB", match_default, make_array(2, 5, -2, -2));
   TEST_INVALID_REGEX("[\\S]", perl);
   TEST_REGEX_SEARCH("\\S+", perl, "  abc  ", match_default, make_array(2, 5, -2, -2));
}

void test_anchors()
{
   // line anchors:
   using namespace boost::regex_constants;
   TEST_REGEX_SEARCH("^ab", extended, "ab", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("^ab", extended, "xxabxx", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("^ab", extended, "xx\nabzz", match_default, make_array(3, 5, -2, -2));
   TEST_REGEX_SEARCH("ab$", extended, "ab", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("ab$", extended, "abxx", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab$", extended, "ab\nzz", match_default, make_array(0, 2, -2, -2));

   TEST_REGEX_SEARCH("^ab", extended, "ab", match_default | match_not_bol | match_not_eol, make_array(-2, -2));
   TEST_REGEX_SEARCH("^ab", extended, "xxabxx", match_default | match_not_bol | match_not_eol, make_array(-2, -2));
   TEST_REGEX_SEARCH("^ab", extended, "xx\nabzz", match_default | match_not_bol | match_not_eol, make_array(3, 5, -2, -2));
   TEST_REGEX_SEARCH("ab$", extended, "ab", match_default | match_not_bol | match_not_eol, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab$", extended, "abxx", match_default | match_not_bol | match_not_eol, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab$", extended, "ab\nzz", match_default | match_not_bol | match_not_eol, make_array(0, 2, -2, -2));

   TEST_REGEX_SEARCH("^ab", extended, "ab", match_default | match_single_line, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("^ab", extended, "xxabxx", match_default | match_single_line, make_array(-2, -2));
   TEST_REGEX_SEARCH("^ab", extended, "xx\nabzz", match_default | match_single_line, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab$", extended, "ab", match_default | match_single_line, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("ab$", extended, "abxx", match_default | match_single_line, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab$", extended, "ab\nzz", match_default | match_single_line, make_array(-2, -2));

   TEST_REGEX_SEARCH("^ab", extended, "ab", match_default | match_not_bol | match_not_eol | match_single_line, make_array(-2, -2));
   TEST_REGEX_SEARCH("^ab", extended, "xxabxx", match_default | match_not_bol | match_not_eol | match_single_line, make_array(-2, -2));
   TEST_REGEX_SEARCH("^ab", extended, "xx\nabzz", match_default | match_not_bol | match_not_eol | match_single_line, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab$", extended, "ab", match_default | match_not_bol | match_not_eol | match_single_line, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab$", extended, "abxx", match_default | match_not_bol | match_not_eol | match_single_line, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab$", extended, "ab\nzz", match_default | match_not_bol | match_not_eol | match_single_line, make_array(-2, -2));
   //
   // changes to newline handling with 2.11:
   //
   TEST_REGEX_SEARCH("^.", extended, "  \n  \r\n  ", match_default, make_array(0, 1, -2, 3, 4, -2, 7, 8, -2, -2));
   TEST_REGEX_SEARCH(".$", extended, "  \n  \r\n  ", match_default, make_array(1, 2, -2, 4, 5, -2, 8, 9, -2, -2));
#if !BOOST_WORKAROUND(__BORLANDC__, < 0x560)
   TEST_REGEX_SEARCH_W(L"^.", extended, L"\x2028 \x2028", match_default, make_array(0, 1, -2, 1, 2, -2, -2));
   TEST_REGEX_SEARCH_W(L".$", extended, L" \x2028 \x2028", match_default, make_array(0, 1, -2, 2, 3, -2, 3, 4, -2, -2));
#endif
}

void test_backrefs()
{
   using namespace boost::regex_constants;
   TEST_INVALID_REGEX("a(b)\\2c", perl);
   TEST_INVALID_REGEX("a(b\\1)c", perl);
   TEST_REGEX_SEARCH("a(b*)c\\1d", perl, "abbcbbd", match_default, make_array(0, 7, 1, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b*)c\\1d", perl, "abbcbd", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("a(b*)c\\1d", perl, "abbcbbbd", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("^(.)\\1", perl, "abc", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("a([bc])\\1d", perl, "abcdabbd", match_default, make_array(4, 8, 5, 6, -2, -2));
   // strictly speaking this is at best ambiguous, at worst wrong, this is what most
   // re implimentations will match though.
   TEST_REGEX_SEARCH("a(([bc])\\2)*d", perl, "abbccd", match_default, make_array(0, 6, 3, 5, 3, 4, -2, -2));
   TEST_REGEX_SEARCH("a(([bc])\\2)*d", perl, "abbcbd", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("a((b)*\\2)*d", perl, "abbbd", match_default, make_array(0, 5, 1, 4, 2, 3, -2, -2));
   TEST_REGEX_SEARCH("(ab*)[ab]*\\1", perl, "ababaaa", match_default, make_array(0, 4, 0, 2, -2, 4, 7, 4, 5, -2, -2));
   TEST_REGEX_SEARCH("(a)\\1bcd", perl, "aabcd", match_default, make_array(0, 5, 0, 1, -2, -2));
   TEST_REGEX_SEARCH("(a)\\1bc*d", perl, "aabcd", match_default, make_array(0, 5, 0, 1, -2, -2));
   TEST_REGEX_SEARCH("(a)\\1bc*d", perl, "aabd", match_default, make_array(0, 4, 0, 1, -2, -2));
   TEST_REGEX_SEARCH("(a)\\1bc*d", perl, "aabcccd", match_default, make_array(0, 7, 0, 1, -2, -2));
   TEST_REGEX_SEARCH("(a)\\1bc*[ce]d", perl, "aabcccd", match_default, make_array(0, 7, 0, 1, -2, -2));
   TEST_REGEX_SEARCH("^(a)\\1b(c)*cd$", perl, "aabcccd", match_default, make_array(0, 7, 0, 1, 4, 5, -2, -2));
   TEST_REGEX_SEARCH("(ab*)[ab]*\\1", extended, "ababaaa", match_default, make_array(0, 7, 0, 1, -2, -2));
}

void test_character_escapes()
{
   using namespace boost::regex_constants;
   // characters by code
   TEST_REGEX_SEARCH("\\0101", perl, "A", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\00", perl, "\0", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\0", perl, "\0", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\0172", perl, "z", match_default, make_array(0, 1, -2, -2));
   // extra escape sequences:
   TEST_REGEX_SEARCH("\\a", perl, "\a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\f", perl, "\f", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\n", perl, "\n", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\r", perl, "\r", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\v", perl, "\v", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\t", perl, "\t", match_default, make_array(0, 1, -2, -2));

   // updated tests for version 2:
   TEST_REGEX_SEARCH("\\x41", perl, "A", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\xff", perl, "\xff", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\xFF", perl, "\xff", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\c@", perl, "\0", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\cA", perl, "\x1", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\cz", perl, "\x3A", match_default, make_array(0, 1, -2, -2));
   TEST_INVALID_REGEX("\\c=", extended);
   TEST_INVALID_REGEX("\\c?", extended);
   TEST_REGEX_SEARCH("=:", perl, "=:", match_default, make_array(0, 2, -2, -2));

   TEST_REGEX_SEARCH("\\e", perl, "\x1B", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\x1b", perl, "\x1B", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\x{1b}", perl, "\x1B", match_default, make_array(0, 1, -2, -2));
   TEST_INVALID_REGEX("\\x{}", perl);
   TEST_INVALID_REGEX("\\x{", perl);
   TEST_INVALID_REGEX("\\x}", perl);
   TEST_INVALID_REGEX("\\x", perl);
   TEST_INVALID_REGEX("\\x{yy", perl);
   TEST_INVALID_REGEX("\\x{1b", perl);
   // \Q...\E sequences:
   TEST_INVALID_REGEX("\\Qabc", perl);
   TEST_INVALID_REGEX("\\Qabc\\", perl);
   TEST_REGEX_SEARCH("\\Qabc\\E", perl, "abcd", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("\\Qabc\\Ed", perl, "abcde", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("\\Q+*?\\\\E", perl, "+*?\\", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("a\\Q+*?\\\\Eb", perl, "a+*?\\b", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("\\C+", perl, "abcde", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("\\X+", perl, "abcde", match_default, make_array(0, 5, -2, -2));
#if !BOOST_WORKAROUND(__BORLANDC__, < 0x560)
   TEST_REGEX_SEARCH_W(L"\\X", perl, L"a\x0300\x0301", match_default, make_array(0, 3, -2, -2));
#endif
}

void test_assertion_escapes()
{
   using namespace boost::regex_constants;
   // word start:
   TEST_REGEX_SEARCH("\\<abcd", perl, "  abcd", match_default, make_array(2, 6, -2, -2));
   TEST_REGEX_SEARCH("\\<ab", perl, "cab", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("\\<ab", perl, "\nab", match_default, make_array(1, 3, -2, -2));
   TEST_REGEX_SEARCH("\\<tag", perl, "::tag", match_default, make_array(2, 5, -2, -2));
   // word end:
   TEST_REGEX_SEARCH("abc\\>", perl, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("abc\\>", perl, "abcd", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("abc\\>", perl, "abc\n", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("abc\\>", perl, "abc::", match_default, make_array(0,3, -2, -2));
   // word boundary:
   TEST_REGEX_SEARCH("\\babcd", perl, "  abcd", match_default, make_array(2, 6, -2, -2));
   TEST_REGEX_SEARCH("\\bab", perl, "cab", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("\\bab", perl, "\nab", match_default, make_array(1, 3, -2, -2));
   TEST_REGEX_SEARCH("\\btag", perl, "::tag", match_default, make_array(2, 5, -2, -2));
   TEST_REGEX_SEARCH("abc\\b", perl, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("abc\\b", perl, "abcd", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("abc\\b", perl, "abc\n", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("abc\\b", perl, "abc::", match_default, make_array(0, 3, -2, -2));
   // within word:
   TEST_REGEX_SEARCH("\\B", perl, "ab", match_default, make_array(1, 1, -2, -2));
   TEST_REGEX_SEARCH("a\\Bb", perl, "ab", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a\\B", perl, "ab", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("a\\B", perl, "a", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("a\\B", perl, "a ", match_default, make_array(-2, -2));
   // buffer operators:
   TEST_REGEX_SEARCH("\\`abc", perl, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("\\`abc", perl, "\nabc", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("\\`abc", perl, " abc", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("abc\\'", perl, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("abc\\'", perl, "abc\n", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("abc\\'", perl, "abc ", match_default, make_array(-2, -2));

   // word start:
   TEST_REGEX_SEARCH("[[:<:]]abcd", perl, "  abcd", match_default, make_array(2, 6, -2, -2));
   TEST_REGEX_SEARCH("[[:<:]]ab", perl, "cab", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("[[:<:]]ab", perl, "\nab", match_default, make_array(1, 3, -2, -2));
   TEST_REGEX_SEARCH("[[:<:]]tag", perl, "::tag", match_default, make_array(2, 5, -2, -2));
   // word end
   TEST_REGEX_SEARCH("abc[[:>:]]", perl, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("abc[[:>:]]", perl, "abcd", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("abc[[:>:]]", perl, "abc\n", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("abc[[:>:]]", perl, "abc::", match_default, make_array(0, 3, -2, -2));

   TEST_REGEX_SEARCH("\\Aabc", perl, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("\\Aabc", perl, "aabc", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("abc\\z", perl, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("abc\\z", perl, "abcd", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("abc\\Z", perl, "abc\n\n", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("abc\\Z", perl, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("\\Gabc", perl, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("\\Gabc", perl, "dabcd", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("a\\Gbc", perl, "abc", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("a\\Aab", perl, "abc", match_default, make_array(-2, -2));
}

void test_tricky_cases()
{
   using namespace boost::regex_constants;
   //
   // now follows various complex expressions designed to try and bust the matcher:
   //
   TEST_REGEX_SEARCH("a(((b)))c", perl, "abc", match_default, make_array(0, 3, 1, 2, 1, 2, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("a(b|(c))d", perl, "abd", match_default, make_array(0, 3, 1, 2, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("a(b|(c))d", perl, "acd", match_default, make_array(0, 3, 1, 2, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("a(b*|c)d", perl, "abbd", match_default, make_array(0, 4, 1, 3, -2, -2));
   // just gotta have one DFA-buster, of course
   TEST_REGEX_SEARCH("a[ab]{20}", perl, "aaaaabaaaabaaaabaaaab", match_default, make_array(0, 21, -2, -2));
   // and an inline expansion in case somebody gets tricky
   TEST_REGEX_SEARCH("a[ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab]", perl, "aaaaabaaaabaaaabaaaab", match_default, make_array(0, 21, -2, -2));
   // and in case somebody just slips in an NFA...
   TEST_REGEX_SEARCH("a[ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab][ab](wee|week)(knights|night)", perl, "aaaaabaaaabaaaabaaaabweeknights", match_default, make_array(0, 31, 21, 24, 24, 31, -2, -2));
   // one really big one
   TEST_REGEX_SEARCH("1234567890123456789012345678901234567890123456789012345678901234567890", perl, "a1234567890123456789012345678901234567890123456789012345678901234567890b", match_default, make_array(1, 71, -2, -2));
   // fish for problems as brackets go past 8
   TEST_REGEX_SEARCH("[ab][cd][ef][gh][ij][kl][mn]", perl, "xacegikmoq", match_default, make_array(1, 8, -2, -2));
   TEST_REGEX_SEARCH("[ab][cd][ef][gh][ij][kl][mn][op]", perl, "xacegikmoq", match_default, make_array(1, 9, -2, -2));
   TEST_REGEX_SEARCH("[ab][cd][ef][gh][ij][kl][mn][op][qr]", perl, "xacegikmoqy", match_default, make_array(1, 10, -2, -2));
   TEST_REGEX_SEARCH("[ab][cd][ef][gh][ij][kl][mn][op][q]", perl, "xacegikmoqy", match_default, make_array(1, 10, -2, -2));
   // and as parenthesis go past 9:
   TEST_REGEX_SEARCH("(a)(b)(c)(d)(e)(f)(g)(h)", perl, "zabcdefghi", match_default, make_array(1, 9, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, -2, -2));
   TEST_REGEX_SEARCH("(a)(b)(c)(d)(e)(f)(g)(h)(i)", perl, "zabcdefghij", match_default, make_array(1, 10, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, -2, -2));
   TEST_REGEX_SEARCH("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)", perl, "zabcdefghijk", match_default, make_array(1, 11, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, -2, -2));
   TEST_REGEX_SEARCH("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)", perl, "zabcdefghijkl", match_default, make_array(1, 12, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, -2, -2));
   TEST_REGEX_SEARCH("(a)d|(b)c", perl, "abc", match_default, make_array(1, 3, -1, -1, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("_+((www)|(ftp)|(mailto)):_*", perl, "_wwwnocolon _mailto:", match_default, make_array(12, 20, 13, 19, -1, -1, -1, -1, 13, 19, -2, -2));
   // subtleties of matching
   TEST_REGEX_SEARCH("a(b)?c\\1d", perl, "acd", match_default, make_array(0, 3, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("a(b?c)+d", perl, "accd", match_default, make_array(0, 4, 2, 3, -2, -2));
   TEST_REGEX_SEARCH("(wee|week)(knights|night)", perl, "weeknights", match_default, make_array(0, 10, 0, 3, 3, 10, -2, -2));
   TEST_REGEX_SEARCH(".*", perl, "abc", match_default, make_array(0, 3, -2, 3, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b|(c))d", perl, "abd", match_default, make_array(0, 3, 1, 2, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("a(b|(c))d", perl, "acd", match_default, make_array(0, 3, 1, 2, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("a(b*|c|e)d", perl, "abbd", match_default, make_array(0, 4, 1, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b*|c|e)d", perl, "acd", match_default, make_array(0, 3, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("a(b*|c|e)d", perl, "ad", match_default, make_array(0, 2, 1, 1, -2, -2));
   TEST_REGEX_SEARCH("a(b?)c", perl, "abc", match_default, make_array(0, 3, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("a(b?)c", perl, "ac", match_default, make_array(0, 2, 1, 1, -2, -2));
   TEST_REGEX_SEARCH("a(b+)c", perl, "abc", match_default, make_array(0, 3, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("a(b+)c", perl, "abbbc", match_default, make_array(0, 5, 1, 4, -2, -2));
   TEST_REGEX_SEARCH("a(b*)c", perl, "ac", match_default, make_array(0, 2, 1, 1, -2, -2));
   TEST_REGEX_SEARCH("(a|ab)(bc([de]+)f|cde)", perl, "abcdef", match_default, make_array(0, 6, 0, 1, 1, 6, 3, 5, -2, -2));
   TEST_REGEX_SEARCH("a([bc]?)c", perl, "abc", match_default, make_array(0, 3, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("a([bc]?)c", perl, "ac", match_default, make_array(0, 2, 1, 1, -2, -2));
   TEST_REGEX_SEARCH("a([bc]+)c", perl, "abc", match_default, make_array(0, 3, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("a([bc]+)c", perl, "abcc", match_default, make_array(0, 4, 1, 3, -2, -2));
   TEST_REGEX_SEARCH("a([bc]+)bc", perl, "abcbc", match_default, make_array(0, 5, 1, 3, -2, -2));
   TEST_REGEX_SEARCH("a(bb+|b)b", perl, "abb", match_default, make_array(0, 3, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("a(bbb+|bb+|b)b", perl, "abb", match_default, make_array(0, 3, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("a(bbb+|bb+|b)b", perl, "abbb", match_default, make_array(0, 4, 1, 3, -2, -2));
   TEST_REGEX_SEARCH("a(bbb+|bb+|b)bb", perl, "abbb", match_default, make_array(0, 4, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("(.*).*", perl, "abcdef", match_default, make_array(0, 6, 0, 6, -2, 6, 6, 6, 6, -2, -2));
   TEST_REGEX_SEARCH("(a*)*", perl, "bc", match_default, make_array(0, 0, 0, 0, -2, 1, 1, 1, 1, -2, 2, 2, 2, 2, -2, -2));
   TEST_REGEX_SEARCH("xyx*xz", perl, "xyxxxxyxxxz", match_default, make_array(5, 11, -2, -2));
   // do we get the right subexpression when it is used more than once?
   TEST_REGEX_SEARCH("a(b|c)*d", perl, "ad", match_default, make_array(0, 2, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("a(b|c)*d", perl, "abcd", match_default, make_array(0, 4, 2, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b|c)+d", perl, "abd", match_default, make_array(0, 3, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("a(b|c)+d", perl, "abcd", match_default, make_array(0, 4, 2, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b|c?)+d", perl, "ad", match_default, make_array(0, 2, 1, 1, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){0,0}d", perl, "ad", match_default, make_array(0, 2, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){0,1}d", perl, "ad", match_default, make_array(0, 2, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){0,1}d", perl, "abd", match_default, make_array(0, 3, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){0,2}d", perl, "ad", match_default, make_array(0, 2, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){0,2}d", perl, "abcd", match_default, make_array(0, 4, 2, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){0,}d", perl, "ad", match_default, make_array(0, 2, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){0,}d", perl, "abcd", match_default, make_array(0, 4, 2, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){1,1}d", perl, "abd", match_default, make_array(0, 3, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){1,2}d", perl, "abd", match_default, make_array(0, 3, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){1,2}d", perl, "abcd", match_default, make_array(0, 4, 2, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){1,}d", perl, "abd", match_default, make_array(0, 3, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){1,}d", perl, "abcd", match_default, make_array(0, 4, 2, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){2,2}d", perl, "acbd", match_default, make_array(0, 4, 2, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){2,2}d", perl, "abcd", match_default, make_array(0, 4, 2, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){2,4}d", perl, "abcd", match_default, make_array(0, 4, 2, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){2,4}d", perl, "abcbd", match_default, make_array(0, 5, 3, 4, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){2,4}d", perl, "abcbcd", match_default, make_array(0, 6, 4, 5, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){2,}d", perl, "abcd", match_default, make_array(0, 4, 2, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b|c){2,}d", perl, "abcbd", match_default, make_array(0, 5, 3, 4, -2, -2));
   // perl only:
   TEST_REGEX_SEARCH("a(b|c?)+d", perl, "abcd", match_default, make_array(0, 4, 3, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b+|((c)*))+d", perl, "abd", match_default, make_array(0, 3, 2, 2, 2, 2, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("a(b+|((c)*))+d", perl, "abcd", match_default, make_array(0, 4, 3, 3, 3, 3, 2, 3, -2, -2));
   // posix only:
   TEST_REGEX_SEARCH("a(b|c?)+d", extended, "abcd", match_default, make_array(0, 4, 2, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b|((c)*))+d", extended, "abcd", match_default, make_array(0, 4, 2, 3, 2, 3, 2, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b+|((c)*))+d", extended, "abd", match_default, make_array(0, 3, 1, 2, -1, -1, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("a(b+|((c)*))+d", extended, "abcd", match_default, make_array(0, 4, 2, 3, 2, 3, 2, 3, -2, -2));
   // literals:
   TEST_REGEX_SEARCH("\\**?/{}", literal, "\\**?/{}", match_default, make_array(0, 7, -2, -2));
   // try to match C++ syntax elements:
   // line comment:
   TEST_REGEX_SEARCH("//[^\\n]*", perl, "++i //here is a line comment\n", match_default, make_array(4, 28, -2, -2));
   // block comment:
   TEST_REGEX_SEARCH("/\\*([^*]|\\*+[^*/])*\\*+/", perl, "/* here is a block comment */", match_default, make_array(0, 29, 26, 27, -2, -2));
   TEST_REGEX_SEARCH("/\\*([^*]|\\*+[^*/])*\\*+/", perl, "/**/", match_default, make_array(0, 4, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("/\\*([^*]|\\*+[^*/])*\\*+/", perl, "/***/", match_default, make_array(0, 5, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("/\\*([^*]|\\*+[^*/])*\\*+/", perl, "/****/", match_default, make_array(0, 6, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("/\\*([^*]|\\*+[^*/])*\\*+/", perl, "/*****/", match_default, make_array(0, 7, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("/\\*([^*]|\\*+[^*/])*\\*+/", perl, "/*****/*/", match_default, make_array(0, 7, -1, -1, -2, -2));
   // preprossor directives:
   TEST_REGEX_SEARCH("^[[:blank:]]*#([^\\n]*\\\\[[:space:]]+)*[^\\n]*", perl, "#define some_symbol", match_default, make_array(0, 19, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("^[[:blank:]]*#([^\\n]*\\\\[[:space:]]+)*[^\\n]*", perl, "#define some_symbol(x) #x", match_default, make_array(0, 25, -1, -1, -2, -2));
   // perl only:
   TEST_REGEX_SEARCH("^[[:blank:]]*#([^\\n]*\\\\[[:space:]]+)*[^\\n]*", perl, "#define some_symbol(x) \\  \r\n  foo();\\\r\n   printf(#x);", match_default, make_array(0, 53, 30, 42, -2, -2));
   // literals:
}

void test_tricky_cases2()
{
   using namespace boost::regex_constants;
   TEST_REGEX_SEARCH("((0x[[:xdigit:]]+)|([[:digit:]]+))u?((int(8|16|32|64))|L)?", perl, "0xFF", match_default, make_array(0, 4, 0, 4,	0, 4,	-1, -1, -1, -1, -1, -1, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("((0x[[:xdigit:]]+)|([[:digit:]]+))u?((int(8|16|32|64))|L)?", perl, "35", match_default, make_array(0, 2, 0, 2, -1, -1, 0, 2, -1, -1, -1, -1, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("((0x[[:xdigit:]]+)|([[:digit:]]+))u?((int(8|16|32|64))|L)?", perl, "0xFFu", match_default, make_array(0, 5, 0, 4, 0, 4, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("((0x[[:xdigit:]]+)|([[:digit:]]+))u?((int(8|16|32|64))|L)?", perl, "0xFFL", match_default, make_array(0, 5, 0, 4, 0, 4, -1, -1, 4, 5, -1, -1, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("((0x[[:xdigit:]]+)|([[:digit:]]+))u?((int(8|16|32|64))|L)?", perl, "0xFFFFFFFFFFFFFFFFuint64", match_default, make_array(0, 24,	0, 18, 0, 18, -1, -1, 19, 24, 19, 24, 22, 24, -2, -2));
   // strings:
   TEST_REGEX_SEARCH("'([^\\\\']|\\\\.)*'", perl, "'\\x3A'", match_default, make_array(0, 6, 4, 5, -2, -2));
   TEST_REGEX_SEARCH("'([^\\\\']|\\\\.)*'", perl, "'\\''", match_default, make_array(0, 4, 1, 3, -2, -2));
   TEST_REGEX_SEARCH("'([^\\\\']|\\\\.)*'", perl, "'\\n'", match_default, make_array(0, 4, 1, 3, -2, -2));
   // posix only:
   TEST_REGEX_SEARCH("^[[:blank:]]*#([^\\n]*\\\\[[:space:]]+)*[^\\n]*", awk, "#define some_symbol(x) \\  \r\n  foo();\\\r\n   printf(#x);", match_default, make_array(0, 53, 28, 42, -2, -2));
   // now try and test some unicode specific characters:
#if !BOOST_WORKAROUND(__BORLANDC__, < 0x560)
   TEST_REGEX_SEARCH_W(L"[[:unicode:]]+", perl, L"a\x0300\x0400z", match_default, make_array(1, 3, -2, -2));
   TEST_REGEX_SEARCH_W(L"[\x10-\xff]", perl, L"\x0300\x0400", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH_W(L"[\01-\05]{5}", perl, L"\x0300\x0400\x0300\x0400\x0300\x0400", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH_W(L"[\x300-\x400]+", perl, L"\x0300\x0400\x0300\x0400\x0300\x0400", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH_W(L"[\\x{300}-\\x{400}]+", perl, L"\x0300\x0400\x0300\x0400\x0300\x0400", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH_W(L"\\x{300}\\x{400}+", perl, L"\x0300\x0400\x0400\x0400\x0400\x0400", match_default, make_array(0, 6, -2, -2));
#endif
   // finally try some case insensitive matches:
   TEST_REGEX_SEARCH("0123456789@abcdefghijklmnopqrstuvwxyz\\[\\\\\\]\\^_`ABCDEFGHIJKLMNOPQRSTUVWXYZ\\{\\|\\}", perl|icase, "0123456789@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}", match_default, make_array(0, 72, -2, -2));
   TEST_REGEX_SEARCH("a", perl|icase, "A", match_default, make_array(0, 1, -2, -2));   
   TEST_REGEX_SEARCH("A", perl|icase, "a", match_default, make_array(0, 1, -2, -2));   
   TEST_REGEX_SEARCH("[abc]+", perl|icase, "abcABC", match_default, make_array(0, 6, -2, -2));   
   TEST_REGEX_SEARCH("[ABC]+", perl|icase, "abcABC", match_default, make_array(0, 6, -2, -2));   
   TEST_REGEX_SEARCH("[a-z]+", perl|icase, "abcABC", match_default, make_array(0, 6, -2, -2));   
   TEST_REGEX_SEARCH("[A-Z]+", perl|icase, "abzANZ", match_default, make_array(0, 6, -2, -2));   
   TEST_REGEX_SEARCH("[a-Z]+", perl|icase, "abzABZ", match_default, make_array(0, 6, -2, -2));   
   TEST_REGEX_SEARCH("[A-z]+", perl|icase, "abzABZ", match_default, make_array(0, 6, -2, -2));   
   TEST_REGEX_SEARCH("[[:lower:]]+", perl|icase, "abyzABYZ", match_default, make_array(0, 8, -2, -2));   
   TEST_REGEX_SEARCH("[[:upper:]]+", perl|icase, "abzABZ", match_default, make_array(0, 6, -2, -2));   
   TEST_REGEX_SEARCH("[[:word:]]+", perl|icase, "abcZZZ", match_default, make_array(0, 6, -2, -2));   
   TEST_REGEX_SEARCH("[[:alpha:]]+", perl|icase, "abyzABYZ", match_default, make_array(0, 8, -2, -2));   
   TEST_REGEX_SEARCH("[[:alnum:]]+", perl|icase, "09abyzABYZ", match_default, make_array(0, 10, -2, -2));   

   // known and suspected bugs:
   TEST_REGEX_SEARCH("\\(", perl, "(", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\)", perl, ")", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\$", perl, "$", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\^", perl, "^", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\.", perl, ".", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\*", perl, "*", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\+", perl, "+", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\?", perl, "?", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\[", perl, "[", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\]", perl, "]", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\|", perl, "|", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\\\", perl, "\\", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("#", perl, "#", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\#", perl, "#", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("a-", perl, "a-", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("\\-", perl, "-", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\{", perl, "{", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\}", perl, "}", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("0", perl, "0", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("1", perl, "1", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("9", perl, "9", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("b", perl, "b", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("B", perl, "B", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("<", perl, "<", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH(">", perl, ">", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("w", perl, "w", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("W", perl, "W", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("`", perl, "`", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH(" ", perl, " ", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\n", perl, "\n", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH(",", perl, ",", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("a", perl, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("f", perl, "f", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("n", perl, "n", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("r", perl, "r", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("t", perl, "t", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("v", perl, "v", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("c", perl, "c", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("x", perl, "x", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH(":", perl, ":", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("(\\.[[:alnum:]]+){2}", perl, "w.a.b ", match_default, make_array(1, 5, 3, 5, -2, -2));

   // new bugs detected in spring 2003:
   TEST_REGEX_SEARCH("b", perl, "abc", match_default|match_continuous, make_array(-2, -2));
   TEST_REGEX_SEARCH("(?!foo)bar", perl, "foobar", match_default, make_array(3, 6, -2, -2));
   TEST_REGEX_SEARCH("(?!foo)bar", perl, "??bar", match_default, make_array(2, 5, -2, -2));
   TEST_REGEX_SEARCH("(?!foo)bar", perl, "barfoo", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("(?!foo)bar", perl, "bar??", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("(?!foo)bar", perl, "bar", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a\\Z", perl, "a\nb", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("()", perl, "abc", match_default, make_array(0, 0, 0, 0, -2, 1, 1, 1, 1, -2, 2, 2, 2, 2, -2, 3, 3, 3, 3, -2, -2));
   TEST_REGEX_SEARCH("^()", perl, "abc", match_default, make_array(0, 0, 0, 0, -2, -2));
   TEST_REGEX_SEARCH("^()+", perl, "abc", match_default, make_array(0, 0, 0, 0, -2, -2));
   TEST_REGEX_SEARCH("^(){1}", perl, "abc", match_default, make_array(0, 0, 0, 0, -2, -2));
   TEST_REGEX_SEARCH("^(){2}", perl, "abc", match_default, make_array(0, 0, 0, 0, -2, -2));
   TEST_REGEX_SEARCH("^((){2})", perl, "abc", match_default, make_array(0, 0, 0, 0, 0, 0, -2, -2));
   TEST_REGEX_SEARCH("()", perl, "", match_default, make_array(0, 0, 0, 0, -2, -2));
   TEST_REGEX_SEARCH("()\\1", perl, "", match_default, make_array(0, 0, 0, 0, -2, -2));
   TEST_REGEX_SEARCH("()\\1", perl, "a", match_default, make_array(0, 0, 0, 0, -2, 1, 1, 1, 1, -2, -2));
   TEST_REGEX_SEARCH("a()\\1b", perl, "ab", match_default, make_array(0, 2, 1, 1, -2, -2));
   TEST_REGEX_SEARCH("a()b\\1", perl, "ab", match_default, make_array(0, 2, 1, 1, -2, -2));
   TEST_REGEX_SEARCH("([a-c]+)\\1", perl, "abcbc", match_default, make_array(1, 5, 1, 3, -2, -2));
   TEST_REGEX_SEARCH(".+abc", perl, "xxxxxxxxyyyyyyyyab", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("(.+)\\1", perl, "abcdxxxyyyxxxyyy", match_default, make_array(4, 16, 4, 10, -2, -2));
   // this should not throw:
   TEST_REGEX_SEARCH("[_]+$", perl, "___________________________________________x", match_default, make_array(-2, -2));

   //
   // the strings in the next test case are too long for most compilers to cope with,
   // we have to break them up and call the testing procs directly rather than rely on the macros:
   //
   static const char* big_text = "00001 01 \r\n00002 02 1         2         3         4         5         6"
      "7         8         9         0\r\n00003 03 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\r\n"
      "00004 04 \r\n00005 05 \r\n00006 06                                                                      "
      "Seite: 0001\r\n00007 07                                                             "
      "StartSeitEEnde: 0001\r\n00008 08                                                             "
      "StartSeiTe Ende: 0001\r\n00009 09                                                             "
      "Start seiteEnde: 0001\r\n00010 10                                                             "
      "28.2.03\r\n00011 11                                                             "
      "Page: 0001\r\n00012 12                                                             "
      "Juhu die Erste: 0001\r\n00013 13                                                             "
      "Es war einmal! 0001\r\n00014 14                               ABCDEFGHIJKLMNOPQRSTUVWXYZ0001\r\n"
      "00015 15                               abcdefghijklmnopqrstuvwxyz0001\r\n"
      "00016 16                               lars.schmeiser@gft.com\r\n00017 17 \r\n"
      "00018 18 \r\n00019 19 \r\n00020 20 \r\n00021 21 1         2         3         4         5         "
      "6         7         8         9         0\r\n"
      "00022 22 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\r\n"
      "00023 01 \r\n00024 02 1         2         3         4         5         6         7         8         9         0\r\n"
      "00025 03 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\r\n"
      "00026 04 \r\n00027 05 \r\n00028 06                                                             "
      "Seite: 0002\r\n00029 07                                                             StartSeitEEnde: 0002\r\n"
      "00030 08                                                             "
      "StartSeiTe Ende: 0002\r\n00031 09                                                             "
      "Start seiteEnde: 0002\r\n00032 10                                                             "
      "28.02.2003\r\n00033 11                                                             "
      "Page: 0002\r\n00034 12                                                             "
      "Juhu die Erste: 0002\r\n00035 13                                                             "
      "Es war einmal! 0002\r\n00036 14                               ABCDEFGHIJKLMNOPQRSTUVWXYZ0002\r\n00037 "
      "15                               abcdefghijklmnopqrstuvwxyz0002\r\n00038 16                               "
      "lars.schmeiser@194.1.12.111\r\n00039 17 \r\n00040 18 \r\n00041 19 \r\n"
      "00042 20 \r\n00043 21 1         2         3         4         5         6         7         8         9         0\r\n";
   
   do{
      test_info<char>::set_info(__FILE__, __LINE__, 
         "(.*\\r\\n){3}.* abcdefghijklmnopqrstuvwxyz.*\\r\\n", 
         perl, big_text, match_default|match_not_dot_newline, 
         make_array(753, 1076, 934, 1005, -2, 2143, 2466, 2324, 2395, -2, -2));
      test(char(0), test_regex_search_tag());
   }while(0);
#if !defined(BOOST_NO_WREGEX) && !defined(BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS)
   do{
      std::string st(big_text);
      test_info<wchar_t>::set_info(__FILE__, __LINE__, 
         L"(.*\\r\\n){3}.* abcdefghijklmnopqrstuvwxyz.*\\r\\n", 
         perl, std::wstring(st.begin(), st.end()), match_default|match_not_dot_newline, 
         make_array(753, 1076, 934, 1005, -2, 2143, 2466, 2324, 2395, -2, -2));
      test(char(0), test_regex_search_tag());
   }while(0);
#endif
}

void test_grep()
{
   //
   // now test grep,
   // basically check all our restart types - line, word, etc
   // checking each one for null and non-null matches.
   //
   using namespace boost::regex_constants;
   TEST_REGEX_SEARCH("a", perl|nosubs, " a a a aa", match_default, make_array(1, 2, -2, 3, 4, -2, 5, 6, -2, 7, 8, -2, 8, 9, -2, -2));
   TEST_REGEX_SEARCH("a+b+", perl|nosubs, "aabaabbb ab", match_default, make_array(0, 3, -2, 3, 8, -2, 9, 11, -2, -2));
   TEST_REGEX_SEARCH("a(b*|c|e)d", perl|nosubs, "adabbdacd", match_default, make_array(0, 2, -2, 2, 6, -2, 6, 9, -2, -2));
   TEST_REGEX_SEARCH("a", perl|nosubs, "\na\na\na\naa", match_default, make_array(1, 2, -2, 3, 4, -2, 5, 6, -2, 7, 8, -2, 8, 9, -2, -2));
   TEST_REGEX_SEARCH("^", perl|nosubs, "   \n\n  \n\n\n", match_default, make_array(0, 0, -2, 4, 4, -2, 5, 5, -2, 8, 8, -2, 9, 9, -2, 10, 10, -2, -2));
   TEST_REGEX_SEARCH("^ab", perl|nosubs, "ab  \nab  ab\n", match_default, make_array(0, 2, -2, 5, 7, -2, -2));
   TEST_REGEX_SEARCH("^[^\\n]*\n", perl|nosubs, "   \n  \n\n  \n", match_default, make_array(0, 4, -2, 4, 7, -2, 7, 8, -2, 8, 11, -2, -2));
   TEST_REGEX_SEARCH("\\<abc", perl|nosubs, "abcabc abc\n\nabc", match_default, make_array(0, 3, -2, 7, 10, -2, 12, 15, -2, -2));
   TEST_REGEX_SEARCH("\\<", perl|nosubs, "  ab a aaa  ", match_default, make_array(2, 2, -2, 5, 5, -2, 7, 7, -2, -2));
   TEST_REGEX_SEARCH("\\<\\w+\\W+", perl|nosubs, " aa  aa  a ", match_default, make_array(1, 5, -2, 5, 9, -2, 9, 11, -2, -2));

   TEST_REGEX_SEARCH("\\Aabc", perl|nosubs, "abc   abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("\\G\\w+\\W+", perl|nosubs, "abc  abc a cbbb   ", match_default, make_array(0, 5, -2, 5, 9, -2, 9, 11, -2, 11, 18, -2, -2));
   TEST_REGEX_SEARCH("\\Ga+b+", perl|nosubs, "aaababb  abb", match_default, make_array(0, 4, -2, 4, 7, -2, -2));
   TEST_REGEX_SEARCH("abc", perl|nosubs, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("abc", perl|nosubs, " abc abcabc", match_default, make_array(1, 4, -2, 5, 8, -2, 8, 11, -2, -2));
   TEST_REGEX_SEARCH("\\n\\n", perl|nosubs, " \n\n\n       \n      \n\n\n\n  ", match_default, make_array(1, 3, -2, 18, 20, -2, 20, 22, -2, -2));
   TEST_REGEX_SEARCH("$", perl|nosubs, "   \n\n  \n\n\n", match_default, make_array(3, 3, -2, 4, 4, -2, 7, 7, -2, 8, 8, -2, 9, 9, -2, 10, 10, -2, -2));
   TEST_REGEX_SEARCH("\\b", perl|nosubs, "  abb a abbb ", match_default, make_array(2, 2, -2, 5, 5, -2, 6, 6, -2, 7, 7, -2, 8, 8, -2, 12, 12, -2, -2));
   TEST_REGEX_SEARCH("A", perl|icase|nosubs, " a a a aa", match_default, make_array(1, 2, -2, 3, 4, -2, 5, 6, -2, 7, 8, -2, 8, 9, -2, -2));
   TEST_REGEX_SEARCH("A+B+", perl|icase|nosubs, "aabaabbb ab", match_default, make_array(0, 3, -2, 3, 8, -2, 9, 11, -2, -2));
   TEST_REGEX_SEARCH("A(B*|c|e)D", perl|icase|nosubs, "adabbdacd", match_default, make_array(0, 2, -2, 2, 6, -2, 6, 9, -2, -2));
   TEST_REGEX_SEARCH("A", perl|icase|nosubs, "\na\na\na\naa", match_default, make_array(1, 2, -2, 3, 4, -2, 5, 6, -2, 7, 8, -2, 8, 9, -2, -2));
   TEST_REGEX_SEARCH("^aB", perl|icase|nosubs, "Ab  \nab  Ab\n", match_default, make_array(0, 2, -2, 5, 7, -2, -2));
   TEST_REGEX_SEARCH("\\<abc", perl|icase|nosubs, "Abcabc aBc\n\nabc", match_default, make_array(0, 3, -2, 7, 10, -2, 12, 15, -2, -2));
   TEST_REGEX_SEARCH("ABC", perl|icase|nosubs, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("abc", perl|icase|nosubs, " ABC ABCABC ", match_default, make_array(1, 4, -2, 5, 8, -2, 8, 11, -2, -2));
}

void test_replace()
{
   using namespace boost::regex_constants;
   // start by testing subs:
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_no_copy, "$`", "...");
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_no_copy, "$'", ",,,");
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_no_copy, "$&", "aaa");
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_no_copy, "$0", "aaa");
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_no_copy, "$1", "");
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_no_copy, "$15", "");
   TEST_REGEX_REPLACE("(a+)b+", perl, "...aaabbb,,,", match_default|format_no_copy, "$1", "aaa");
   TEST_REGEX_REPLACE("[[:digit:]]*", perl, "123ab", match_default|format_no_copy, "<$0>", "<123><><><>");
   TEST_REGEX_REPLACE("[[:digit:]]*", perl, "123ab1", match_default|format_no_copy, "<$0>", "<123><><><1>");
   // and now escapes:
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_no_copy, "$x", "$x");
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_no_copy, "\\a", "\a");
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_no_copy, "\\f", "\f");
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_no_copy, "\\n", "\n");
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_no_copy, "\\r", "\r");
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_no_copy, "\\t", "\t");
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_no_copy, "\\x21", "!");
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_no_copy, "\\x{21}", "!");
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_no_copy, "\\c@", "\0");
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_no_copy, "\\e", "\x1B");
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_no_copy, "\\0101", "A");
   // sed format sequences:
   TEST_REGEX_REPLACE("(a+)(b+)", perl, " ...aabb,,", match_default|format_sed|format_no_copy, "\\0", "aabb");
   TEST_REGEX_REPLACE("(a+)(b+)", perl, " ...aabb,,", match_default|format_sed|format_no_copy, "\\1", "aa");
   TEST_REGEX_REPLACE("(a+)(b+)", perl, " ...aabb,,", match_default|format_sed|format_no_copy, "\\2", "bb");
   TEST_REGEX_REPLACE("(a+)(b+)", perl, " ...aabb,,", match_default|format_sed|format_no_copy, "&", "aabb");
   TEST_REGEX_REPLACE("(a+)(b+)", perl, " ...aabb,,", match_default|format_sed|format_no_copy, "$", "$");
   TEST_REGEX_REPLACE("(a+)(b+)", perl, " ...aabb,,", match_default|format_sed|format_no_copy, "$1", "$1");
   TEST_REGEX_REPLACE("(a+)(b+)", perl, " ...aabb,,", match_default|format_sed|format_no_copy, "()?:", "()?:");
   TEST_REGEX_REPLACE("(a+)(b+)", perl, " ...aabb,,", match_default|format_sed|format_no_copy, "\\\\", "\\");
   TEST_REGEX_REPLACE("(a+)(b+)", perl, " ...aabb,,", match_default|format_sed|format_no_copy, "\\&", "&");

   TEST_REGEX_REPLACE("(a+)(b+)", perl, " ...aabb,,", match_default|format_perl|format_no_copy, "$0", "aabb");
   TEST_REGEX_REPLACE("(a+)(b+)", perl, " ...aabb,,", match_default|format_perl|format_no_copy, "$1", "aa");
   TEST_REGEX_REPLACE("(a+)(b+)", perl, " ...aabb,,", match_default|format_perl|format_no_copy, "$2", "bb");
   TEST_REGEX_REPLACE("(a+)(b+)", perl, " ...aabb,,", match_default|format_perl|format_no_copy, "$&", "aabb");
   TEST_REGEX_REPLACE("(a+)(b+)", perl, " ...aabb,,", match_default|format_perl|format_no_copy, "&", "&");
   TEST_REGEX_REPLACE("(a+)(b+)", perl, " ...aabb,,", match_default|format_perl|format_no_copy, "\\0", "\0");
   TEST_REGEX_REPLACE("(a+)(b+)", perl, " ...aabb,,", match_default|format_perl|format_no_copy, "()?:", "()?:");
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,", match_default|format_perl|format_no_copy, "\\0101", "A");

   // move to copying unmatched data:
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_all, "bbb", "...bbb,,,");
   TEST_REGEX_REPLACE("a+(b+)", perl, "...aaabb,,,", match_default|format_all, "$1", "...bb,,,");
   TEST_REGEX_REPLACE("a+(b+)", perl, "...aaabb,,,ab*abbb?", match_default|format_all, "$1", "...bb,,,b*bbb?");
   TEST_REGEX_REPLACE("(a+)|(b+)", perl, "...aaabb,,,ab*abbb?", match_default|format_all, "(?1A)(?2B)", "...AB,,,AB*AB?");
   TEST_REGEX_REPLACE("(a+)|(b+)", perl, "...aaabb,,,ab*abbb?", match_default|format_all, "?1A:B", "...AB,,,AB*AB?");
   TEST_REGEX_REPLACE("(a+)|(b+)", perl, "...aaabb,,,ab*abbb?", match_default|format_all, "(?1A:B)C", "...ACBC,,,ACBC*ACBC?");
   TEST_REGEX_REPLACE("(a+)|(b+)", perl, "...aaabb,,,ab*abbb?", match_default|format_all, "?1:B", "...B,,,B*B?");
   // move to copying unmatched data, but replace first occurance only:
   TEST_REGEX_REPLACE("a+", perl, "...aaa,,,", match_default|format_all|format_first_only, "bbb", "...bbb,,,");
   TEST_REGEX_REPLACE("a+(b+)", perl, "...aaabb,,,", match_default|format_all|format_first_only, "$1", "...bb,,,");
   TEST_REGEX_REPLACE("a+(b+)", perl, "...aaabb,,,ab*abbb?", match_default|format_all|format_first_only, "$1", "...bb,,,ab*abbb?");
   TEST_REGEX_REPLACE("(a+)|(b+)", perl, "...aaabb,,,ab*abbb?", match_default|format_all|format_first_only, "(?1A)(?2B)", "...Abb,,,ab*abbb?");
}

void test_non_greedy_repeats()
{
   //
   // non-greedy repeats added 21/04/00
   //
   using namespace boost::regex_constants;
   TEST_REGEX_SEARCH("a*?", perl, "aa", match_default, make_array(0, 0, -2, 0, 1, -2, 1, 1, -2, 1, 2, -2, 2, 2, -2, -2));
   TEST_REGEX_SEARCH("^a*?$", perl, "aa", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("^.*?$", perl, "aa", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("^(a)*?$", perl, "aa", match_default, make_array(0, 2, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("^[ab]*?$", perl, "aa", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a??", perl, "aa", match_default, make_array(0, 0, -2, 0, 1, -2, 1, 1, -2, 1, 2, -2, 2, 2, -2, -2));
   TEST_REGEX_SEARCH("a+?", perl, "aa", match_default, make_array(0, 1, -2, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("a{1,3}?", perl, "aaa", match_default, make_array(0, 1, -2, 1, 2, -2, 2, 3, -2, -2));
   TEST_REGEX_SEARCH("\\w+?w", perl, "...ccccccwcccccw", match_default, make_array(3, 10, -2, 10, 16, -2, -2));
   TEST_REGEX_SEARCH("\\W+\\w+?w", perl, "...ccccccwcccccw", match_default, make_array(0, 10, -2, -2));
   TEST_REGEX_SEARCH("abc|\\w+?", perl, "abd", match_default, make_array(0, 1, -2, 1, 2, -2, 2, 3, -2, -2));
   TEST_REGEX_SEARCH("abc|\\w+?", perl, "abcd", match_default, make_array(0, 3, -2, 3, 4, -2, -2));
   TEST_REGEX_SEARCH("<\\s*tag[^>]*>(.*?)<\\s*/tag\\s*>", perl, " <tag>here is some text</tag> <tag></tag>", match_default, make_array(1, 29, 6, 23, -2, 30, 41, 35, 35, -2, -2));
   TEST_REGEX_SEARCH("<\\s*tag[^>]*>(.*?)<\\s*/tag\\s*>", perl, " < tag attr=\"something\">here is some text< /tag > <tag></tag>", match_default, make_array(1, 49, 24, 41, -2, 50, 61, 55, 55, -2, -2));
   TEST_INVALID_REGEX("a{1,3}{1}", perl);
   TEST_INVALID_REGEX("a**", perl);
   TEST_INVALID_REGEX("a++", perl);
}

void test_non_marking_paren()
{
   using namespace boost::regex_constants;
   //
   // non-marking parenthesis added 25/04/00
   //
   TEST_REGEX_SEARCH("(?:abc)+", perl, "xxabcabcxx", match_default, make_array(2, 8, -2, -2));
   TEST_REGEX_SEARCH("(?:a+)(b+)", perl, "xaaabbbx", match_default, make_array(1, 7, 4, 7, -2, -2));
   TEST_REGEX_SEARCH("(a+)(?:b+)", perl, "xaaabbba", match_default, make_array(1, 7, 1, 4, -2, -2));
   TEST_REGEX_SEARCH("(?:(a+)b+)", perl, "xaaabbba", match_default, make_array(1, 7, 1, 4, -2, -2));
   TEST_REGEX_SEARCH("(?:a+(b+))", perl, "xaaabbba", match_default, make_array(1, 7, 4, 7, -2, -2));
   TEST_REGEX_SEARCH("a+(?#b+)b+", perl, "xaaabbba", match_default, make_array(1, 7, -2, -2));
   TEST_REGEX_SEARCH("(a)(?:b|$)", perl, "ab", match_default, make_array(0, 2, 0, 1, -2, -2));
   TEST_REGEX_SEARCH("(a)(?:b|$)", perl, "a", match_default, make_array(0, 1, 0, 1, -2, -2));
}

void test_partial_match()
{
   using namespace boost::regex_constants;
   //
   // try some partial matches:
   //
   TEST_REGEX_SEARCH("(xyz)(.*)abc", perl, "xyzaaab", match_default|match_partial, make_array(0, 7, -2, -2));
   TEST_REGEX_SEARCH("(xyz)(.*)abc", perl, "xyz", match_default|match_partial, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("(xyz)(.*)abc", perl, "xy", match_default|match_partial, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("(xyz)(.*)abc", perl, "x", match_default|match_partial, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("(xyz)(.*)abc", perl, "", match_default|match_partial, make_array(-2, -2));
   TEST_REGEX_SEARCH("(xyz)(.*)abc", perl, "aaaa", match_default|match_partial, make_array(-2, -2));
   TEST_REGEX_SEARCH(".abc", perl, "aaab", match_default|match_partial, make_array(1, 4, -2, -2));
   TEST_REGEX_SEARCH("a[_]", perl, "xxa", match_default|match_partial, make_array(2, 3, -2, -2));
}

void test_forward_lookahead_asserts()
{
   //
   // forward lookahead asserts added 21/01/02
   //
   using namespace boost::regex_constants;
   TEST_REGEX_SEARCH("((?:(?!a|b)\\w)+)(\\w+)", perl, "  xxxabaxxx  ", match_default, make_array(2, 11, 2, 5, 5, 11, -2, -2));
   TEST_REGEX_SEARCH("/\\*(?:(?!\\*/).)*\\*/", perl, "  /**/  ", match_default, make_array(2, 6, -2, -2));
   TEST_REGEX_SEARCH("/\\*(?:(?!\\*/).)*\\*/", perl, "  /***/  ", match_default, make_array(2, 7, -2, -2));
   TEST_REGEX_SEARCH("/\\*(?:(?!\\*/).)*\\*/", perl, "  /********/  ", match_default, make_array(2, 12, -2, -2));
   TEST_REGEX_SEARCH("/\\*(?:(?!\\*/).)*\\*/", perl, "  /* comment */  ", match_default, make_array(2, 15, -2, -2));
   TEST_REGEX_SEARCH("<\\s*a[^>]*>((?:(?!<\\s*/\\s*a\\s*>).)*)<\\s*/\\s*a\\s*>", perl, " <a href=\"here\">here</a> ", match_default, make_array(1, 24, 16, 20, -2, -2));
   TEST_REGEX_SEARCH("<\\s*a[^>]*>((?:(?!<\\s*/\\s*a\\s*>).)*)<\\s*/\\s*a\\s*>", perl, " <a href=\"here\">here< /  a > ", match_default, make_array(1, 28, 16, 20, -2, -2));
   TEST_REGEX_SEARCH("<\\s*a[^>]*>((?:(?!<\\s*/\\s*a\\s*>).)*)(?=<\\s*/\\s*a\\s*>)", perl, " <a href=\"here\">here</a> ", match_default, make_array(1, 20, 16, 20, -2, -2));
   TEST_REGEX_SEARCH("<\\s*a[^>]*>((?:(?!<\\s*/\\s*a\\s*>).)*)(?=<\\s*/\\s*a\\s*>)", perl, " <a href=\"here\">here< /  a > ", match_default, make_array(1, 20, 16, 20, -2, -2));
   TEST_REGEX_SEARCH("^(?!^(?:PRN|AUX|CLOCK\\$|NUL|CON|COM\\d|LPT\\d|\\..*)(?:\\..+)?$)[^\\x00-\\x1f\\\\?*:\"|/]+$", perl, "command.com", match_default, make_array(0, 11, -2, -2));
   TEST_REGEX_SEARCH("^(?!^(?:PRN|AUX|CLOCK\\$|NUL|CON|COM\\d|LPT\\d|\\..*)(?:\\..+)?$)[^\\x00-\\x1f\\\\?*:\"|/]+$", perl, "PRN", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("^(?!^(?:PRN|AUX|CLOCK\\$|NUL|CON|COM\\d|LPT\\d|\\..*)(?:\\..+)?$)[^\\x00-\\x1f\\\\?*:\"|/]+$", perl, "COM2", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("^(?=.*\\d).{4,8}$", perl, "abc3", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("^(?=.*\\d).{4,8}$", perl, "abc3def4", match_default, make_array(0, 8, -2, -2));
   TEST_REGEX_SEARCH("^(?=.*\\d).{4,8}$", perl, "ab2", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("^(?=.*\\d).{4,8}$", perl, "abcdefg", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("^(?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).{4,8}$", perl, "abc3", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("^(?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).{4,8}$", perl, "abC3", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("^(?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).{4,8}$", perl, "ABCD3", match_default, make_array(-2, -2));

   // lookbehind assertions, added 2004-04-30
   TEST_REGEX_SEARCH("/\\*.*(?<=\\*)/", perl, "/**/", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("/\\*.*(?<=\\*)/", perl, "/*****/   ", match_default, make_array(0, 7, -2, -2));
   TEST_REGEX_SEARCH("(?<=['\"]).*?(?=['\"])", perl, " 'ac' ", match_default, make_array(2, 4, -2, -2));
   TEST_REGEX_SEARCH("(?<=['\"]).*?(?=['\"])", perl, " \"ac\" ", match_default, make_array(2, 4, -2, -2));
   TEST_REGEX_SEARCH("(?<=['\"]).*?(?<!\\\\)(?=['\"])", perl, " \"ac\" ", match_default, make_array(2, 4, -2, -2));
   TEST_REGEX_SEARCH("(?<=['\"]).*?(?<!\\\\)(?=['\"])", perl, " \"ac\\\"\" ", match_default, make_array(2, 6, -2, -2));
   TEST_INVALID_REGEX("(?<=[abc]", perl);
   TEST_INVALID_REGEX("(?<=", perl);
   TEST_INVALID_REGEX("(?<", perl);
   TEST_INVALID_REGEX("(?", perl);
}

void test_fast_repeats()
{
   using namespace boost::regex_constants;
   // extended repeat checking to exercise new algorithms:
   TEST_REGEX_SEARCH("ab.*xy", perl, "abxy_", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab.*xy", perl, "ab_xy_", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab.*xy", perl, "abxy", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab.*xy", perl, "ab_xy", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab.*", perl, "ab", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("ab.*", perl, "ab__", match_default, make_array(0, 4, -2, -2));

   TEST_REGEX_SEARCH("ab.{2,5}xy", perl, "ab__xy_", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}xy", perl, "ab____xy_", match_default, make_array(0, 8, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}xy", perl, "ab_____xy_", match_default, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}xy", perl, "ab__xy", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}xy", perl, "ab_____xy", match_default, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}", perl, "ab__", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}", perl, "ab_______", match_default, make_array(0, 7, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}xy", perl, "ab______xy", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}xy", perl, "ab_xy", match_default, make_array(-2, -2));
   
   TEST_REGEX_SEARCH("ab.*?xy", perl, "abxy_", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab.*?xy", perl, "ab_xy_", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab.*?xy", perl, "abxy", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab.*?xy", perl, "ab_xy", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab.*?", perl, "ab", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("ab.*?", perl, "ab__", match_default, make_array(0, 2, -2, -2));
   
   TEST_REGEX_SEARCH("ab.{2,5}?xy", perl, "ab__xy_", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}?xy", perl, "ab____xy_", match_default, make_array(0, 8, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}?xy", perl, "ab_____xy_", match_default, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}?xy", perl, "ab__xy", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}?xy", perl, "ab_____xy", match_default, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}?", perl, "ab__", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}?", perl, "ab_______", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}?xy", perl, "ab______xy", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}xy", perl, "ab_xy", match_default, make_array(-2, -2));

   // again but with slower algorithm variant:
   TEST_REGEX_SEARCH("ab.*xy", perl, "abxy_", match_not_dot_newline|match_not_dot_null, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab.*xy", perl, "ab_xy_", match_not_dot_newline|match_not_dot_null, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab.*xy", perl, "abxy", match_not_dot_newline|match_not_dot_null, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab.*xy", perl, "ab_xy", match_not_dot_newline|match_not_dot_null, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab.*", perl, "ab", match_not_dot_newline|match_not_dot_null, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("ab.*", perl, "ab__", match_not_dot_newline|match_not_dot_null, make_array(0, 4, -2, -2));

   TEST_REGEX_SEARCH("ab.{2,5}xy", perl, "ab__xy_", match_not_dot_newline|match_not_dot_null, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}xy", perl, "ab____xy_", match_not_dot_newline|match_not_dot_null, make_array(0, 8, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}xy", perl, "ab_____xy_", match_not_dot_newline|match_not_dot_null, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}xy", perl, "ab__xy", match_not_dot_newline|match_not_dot_null, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}xy", perl, "ab_____xy", match_not_dot_newline|match_not_dot_null, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}", perl, "ab__", match_not_dot_newline|match_not_dot_null, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}", perl, "ab_______", match_not_dot_newline|match_not_dot_null, make_array(0, 7, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}xy", perl, "ab______xy", match_not_dot_newline|match_not_dot_null, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}xy", perl, "ab_xy", match_not_dot_newline|match_not_dot_null, make_array(-2, -2));
   
   TEST_REGEX_SEARCH("ab.*?xy", perl, "abxy_", match_not_dot_newline|match_not_dot_null, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab.*?xy", perl, "ab_xy_", match_not_dot_newline|match_not_dot_null, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab.*?xy", perl, "abxy", match_not_dot_newline|match_not_dot_null, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab.*?xy", perl, "ab_xy", match_not_dot_newline|match_not_dot_null, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab.*?", perl, "ab", match_not_dot_newline|match_not_dot_null, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("ab.*?", perl, "ab__", match_not_dot_newline|match_not_dot_null, make_array(0, 2, -2, -2));
   
   TEST_REGEX_SEARCH("ab.{2,5}?xy", perl, "ab__xy_", match_not_dot_newline|match_not_dot_null, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}?xy", perl, "ab____xy_", match_not_dot_newline|match_not_dot_null, make_array(0, 8, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}?xy", perl, "ab_____xy_", match_not_dot_newline|match_not_dot_null, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}?xy", perl, "ab__xy", match_not_dot_newline|match_not_dot_null, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}?xy", perl, "ab_____xy", match_not_dot_newline|match_not_dot_null, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}?", perl, "ab__", match_not_dot_newline|match_not_dot_null, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}?", perl, "ab_______", match_not_dot_newline|match_not_dot_null, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}?xy", perl, "ab______xy", match_not_dot_newline|match_not_dot_null, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab.{2,5}xy", perl, "ab_xy", match_not_dot_newline|match_not_dot_null, make_array(-2, -2));

   // now again for single character repeats:
   TEST_REGEX_SEARCH("ab_*xy", perl, "abxy_", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab_*xy", perl, "ab_xy_", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab_*xy", perl, "abxy", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab_*xy", perl, "ab_xy", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab_*", perl, "ab", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("ab_*", perl, "ab__", match_default, make_array(0, 4, -2, -2));

   TEST_REGEX_SEARCH("ab_{2,5}xy", perl, "ab__xy_", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab_{2,5}xy", perl, "ab____xy_", match_default, make_array(0, 8, -2, -2));
   TEST_REGEX_SEARCH("ab_{2,5}xy", perl, "ab_____xy_", match_default, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab_{2,5}xy", perl, "ab__xy", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab_{2,5}xy", perl, "ab_____xy", match_default, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab_{2,5}", perl, "ab__", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab_{2,5}", perl, "ab_______", match_default, make_array(0, 7, -2, -2));
   TEST_REGEX_SEARCH("ab_{2,5}xy", perl, "ab______xy", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab_{2,5}xy", perl, "ab_xy", match_default, make_array(-2, -2));
   
   TEST_REGEX_SEARCH("ab_*?xy", perl, "abxy_", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab_*?xy", perl, "ab_xy_", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab_*?xy", perl, "abxy", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab_*?xy", perl, "ab_xy", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab_*?", perl, "ab", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("ab_*?", perl, "ab__", match_default, make_array(0, 2, -2, -2));
   
   TEST_REGEX_SEARCH("ab_{2,5}?xy", perl, "ab__xy_", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab_{2,5}?xy", perl, "ab____xy_", match_default, make_array(0, 8, -2, -2));
   TEST_REGEX_SEARCH("ab_{2,5}?xy", perl, "ab_____xy_", match_default, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab_{2,5}?xy", perl, "ab__xy", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab_{2,5}?xy", perl, "ab_____xy", match_default, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab_{2,5}?", perl, "ab__", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab_{2,5}?", perl, "ab_______", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab_{2,5}?xy", perl, "ab______xy", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab_{2,5}xy", perl, "ab_xy", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("(5*?).somesite", perl, "//555.somesite", match_default, make_array(2, 14, 2, 5, -2, -2));

   // and again for sets:
   TEST_REGEX_SEARCH("ab[_,;]*xy", perl, "abxy_", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]*xy", perl, "ab_xy_", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]*xy", perl, "abxy", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]*xy", perl, "ab_xy", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]*", perl, "ab", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]*", perl, "ab__", match_default, make_array(0, 4, -2, -2));

   TEST_REGEX_SEARCH("ab[_,;]{2,5}xy", perl, "ab__xy_", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]{2,5}xy", perl, "ab____xy_", match_default, make_array(0, 8, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]{2,5}xy", perl, "ab_____xy_", match_default, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]{2,5}xy", perl, "ab__xy", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]{2,5}xy", perl, "ab_____xy", match_default, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]{2,5}", perl, "ab__", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]{2,5}", perl, "ab_______", match_default, make_array(0, 7, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]{2,5}xy", perl, "ab______xy", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab[_,;]{2,5}xy", perl, "ab_xy", match_default, make_array(-2, -2));
   
   TEST_REGEX_SEARCH("ab[_,;]*?xy", perl, "abxy_", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]*?xy", perl, "ab_xy_", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]*?xy", perl, "abxy", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]*?xy", perl, "ab_xy", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]*?", perl, "ab", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]*?", perl, "ab__", match_default, make_array(0, 2, -2, -2));
   
   TEST_REGEX_SEARCH("ab[_,;]{2,5}?xy", perl, "ab__xy_", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]{2,5}?xy", perl, "ab____xy_", match_default, make_array(0, 8, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]{2,5}?xy", perl, "ab_____xy_", match_default, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]{2,5}?xy", perl, "ab__xy", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]{2,5}?xy", perl, "ab_____xy", match_default, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]{2,5}?", perl, "ab__", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]{2,5}?", perl, "ab_______", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab[_,;]{2,5}?xy", perl, "ab______xy", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab[_,;]{2,5}xy", perl, "ab_xy", match_default, make_array(-2, -2));

   // and again for tricky sets with digraphs:
   TEST_REGEX_SEARCH("ab[_[.ae.]]*xy", perl, "abxy_", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]*xy", perl, "ab_xy_", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]*xy", perl, "abxy", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]*xy", perl, "ab_xy", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]*", perl, "ab", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]*", perl, "ab__", match_default, make_array(0, 4, -2, -2));

   TEST_REGEX_SEARCH("ab[_[.ae.]]{2,5}xy", perl, "ab__xy_", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]{2,5}xy", perl, "ab____xy_", match_default, make_array(0, 8, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]{2,5}xy", perl, "ab_____xy_", match_default, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]{2,5}xy", perl, "ab__xy", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]{2,5}xy", perl, "ab_____xy", match_default, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]{2,5}", perl, "ab__", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]{2,5}", perl, "ab_______", match_default, make_array(0, 7, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]{2,5}xy", perl, "ab______xy", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]{2,5}xy", perl, "ab_xy", match_default, make_array(-2, -2));
   
   TEST_REGEX_SEARCH("ab[_[.ae.]]*?xy", perl, "abxy_", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]*?xy", perl, "ab_xy_", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]*?xy", perl, "abxy", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]*?xy", perl, "ab_xy", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]*?", perl, "ab", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]*?", perl, "ab__", match_default, make_array(0, 2, -2, -2));
   
   TEST_REGEX_SEARCH("ab[_[.ae.]]{2,5}?xy", perl, "ab__xy_", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]{2,5}?xy", perl, "ab____xy_", match_default, make_array(0, 8, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]{2,5}?xy", perl, "ab_____xy_", match_default, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]{2,5}?xy", perl, "ab__xy", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]{2,5}?xy", perl, "ab_____xy", match_default, make_array(0, 9, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]{2,5}?", perl, "ab__", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]{2,5}?", perl, "ab_______", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]{2,5}?xy", perl, "ab______xy", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("ab[_[.ae.]]{2,5}xy", perl, "ab_xy", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("([5[.ae.]]*?).somesite", perl, "//555.somesite", match_default, make_array(2, 14, 2, 5, -2, -2));
}

void test_independent_subs()
{
   using namespace boost::regex_constants;
   TEST_REGEX_SEARCH("(?>^abc)", perl, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("(?>^abc)", perl, "def\nabc", match_default, make_array(4, 7, -2, -2));
   TEST_REGEX_SEARCH("(?>^abc)", perl, "defabc", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("(?>.*/)foo", perl, "/this/is/a/very/long/line/in/deed/with/very/many/slashes/in/it/you/see/", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("(?>.*/)foo", perl, "/this/is/a/very/long/line/in/deed/with/very/many/slashes/in/and/foo", match_default, make_array(0, 67, -2, -2));
   TEST_REGEX_SEARCH("(?>(\\.\\d\\d[1-9]?))\\d+", perl, "1.230003938", match_default, make_array(1, 11, 1, 4, -2, -2));
   TEST_REGEX_SEARCH("(?>(\\.\\d\\d[1-9]?))\\d+", perl, "1.875000282", match_default, make_array(1, 11, 1, 5, -2, -2));
   TEST_REGEX_SEARCH("(?>(\\.\\d\\d[1-9]?))\\d+", perl, "1.235", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("^((?>\\w+)|(?>\\s+))*$", perl, "now is the time for all good men to come to the aid of the party", match_default, make_array(0, 64, 59, 64, -2, -2));
   TEST_REGEX_SEARCH("^((?>\\w+)|(?>\\s+))*$", perl, "this is not a line with only words and spaces!", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("((?>\\d+))(\\w)", perl, "12345a", match_default, make_array(0, 6, 0, 5, 5, 6, -2, -2));
   TEST_REGEX_SEARCH("((?>\\d+))(\\w)", perl, "12345+", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("((?>\\d+))(\\d)", perl, "12345", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("(?>a+)b", perl, "aaab", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("((?>a+)b)", perl, "aaab", match_default, make_array(0, 4, 0, 4, -2, -2));
   TEST_REGEX_SEARCH("(?>(a+))b", perl, "aaab", match_default, make_array(0, 4, 0, 3, -2, -2));
   TEST_REGEX_SEARCH("(?>b)+", perl, "aaabbbccc", match_default, make_array(3, 6, -2, -2));
   TEST_REGEX_SEARCH("(?>a+|b+|c+)*c", perl, "aaabbbbccccd", match_default, make_array(0, 8, -2, 8, 9, -2, 9, 10, -2, 10, 11, -2, -2));
   TEST_REGEX_SEARCH("((?>[^()]+)|\\([^()]*\\))+", perl, "((abc(ade)ufh()()x", match_default, make_array(2, 18, 17, 18, -2, -2));
   TEST_REGEX_SEARCH("\\(((?>[^()]+)|\\([^()]+\\))+\\)", perl, "(abc)", match_default, make_array(0, 5, 1, 4, -2, -2));
   TEST_REGEX_SEARCH("\\(((?>[^()]+)|\\([^()]+\\))+\\)", perl, "(abc(def)xyz)", match_default, make_array(0, 13, 9, 12, -2, -2));
   TEST_REGEX_SEARCH("\\(((?>[^()]+)|\\([^()]+\\))+\\)", perl, "((()aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", match_default, make_array(-2, -2));

   TEST_REGEX_SEARCH("(?>a*)*", perl, "a", match_default, make_array(0, 1, -2, 1, 1, -2, -2));
   TEST_REGEX_SEARCH("(?>a*)*", perl, "aa", match_default, make_array(0, 2, -2, 2, 2, -2, -2));
   TEST_REGEX_SEARCH("(?>a*)*", perl, "aaaa", match_default, make_array(0, 4, -2, 4, 4, -2, -2));
   TEST_REGEX_SEARCH("(?>a*)*", perl, "a", match_default, make_array(0, 1, -2, 1, 1, -2, -2));
   TEST_REGEX_SEARCH("(?>a*)*", perl, "aaabcde", match_default, make_array(0, 3, -2, 3, 3, -2, 4, 4, -2, 5, 5, -2, 6, 6, -2, 7, 7, -2, -2));
   TEST_REGEX_SEARCH("((?>a*))*", perl, "aaaaa", match_default, make_array(0, 5, 5, 5, -2, 5, 5, 5, 5, -2, -2));
   TEST_REGEX_SEARCH("((?>a*))*", perl, "aabbaa", match_default, make_array(0, 2, 2, 2, -2, 2, 2, 2, 2, -2, 3, 3, 3, 3, -2, 4, 6, 6, 6, -2, 6, 6, 6, 6, -2, -2));
   TEST_REGEX_SEARCH("((?>a*?))*", perl, "aaaaa", match_default, make_array(0, 0, 0, 0, -2, 1, 1, 1, 1, -2, 2, 2, 2, 2, -2, 3, 3, 3, 3, -2, 4, 4, 4, 4, -2, 5, 5, 5, 5, -2, -2));
   TEST_REGEX_SEARCH("((?>a*?))*", perl, "aabbaa", match_default, make_array(0, 0, 0, 0, -2, 1, 1, 1, 1, -2, 2, 2, 2, 2, -2, 3, 3, 3, 3, -2, 4, 4, 4, 4, -2, 5, 5, 5, 5, -2, 6, 6, 6, 6, -2, -2));
   TEST_REGEX_SEARCH("word (?>(?:(?!otherword)[a-zA-Z0-9]+ ){0,30})otherword", perl, "word cat dog elephant mussel cow horse canary baboon snake shark otherword", match_default, make_array(0, 74, -2, -2));
   TEST_REGEX_SEARCH("word (?>(?:(?!otherword)[a-zA-Z0-9]+ ){0,30})otherword", perl, "word cat dog elephant mussel cow horse canary baboon snake shark", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("word (?>[a-zA-Z0-9]+ ){0,30}otherword", perl, "word cat dog elephant mussel cow horse canary baboon snake shark the quick brown fox and the lazy dog and several other words getting close to thirty by now I hope", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("word (?>[a-zA-Z0-9]+ ){0,30}otherword", perl, "word cat dog elephant mussel cow horse canary baboon snake shark the quick brown fox and the lazy dog and several other words getting close to thirty by now I really really hope otherword", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("((?>Z)+|A)+", perl, "ZABCDEFG", match_default, make_array(0, 2, 1, 2, -2, -2));
   TEST_INVALID_REGEX("((?>)+|A)+", perl);
}

void test_nosubs()
{
   using namespace boost::regex_constants;
   // subtleties of matching with no sub-expressions marked
   TEST_REGEX_SEARCH("a(b?c)+d", perl, "accd", match_default|match_nosubs, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("(wee|week)(knights|night)", perl, "weeknights", match_default|match_nosubs, make_array(0, 10, -2, -2));
   TEST_REGEX_SEARCH(".*", perl, "abc", match_default|match_nosubs, make_array(0, 3, -2, 3, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b|(c))d", perl, "abd", match_default|match_nosubs, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b|(c))d", perl, "acd", match_default|match_nosubs, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b*|c|e)d", perl, "abbd", match_default|match_nosubs, make_array(0, 4, -2, -2));
   
   TEST_REGEX_SEARCH("a(b*|c|e)d", perl, "acd", match_default|match_nosubs, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b*|c|e)d", perl, "ad", match_default|match_nosubs, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a(b?)c", perl, "abc", match_default|match_nosubs, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b?)c", perl, "ac", match_default|match_nosubs, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a(b+)c", perl, "abc", match_default|match_nosubs, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b+)c", perl, "abbbc", match_default|match_nosubs, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("a(b*)c", perl, "ac", match_default|match_nosubs, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("(a|ab)(bc([de]+)f|cde)", perl, "abcdef", match_default|match_nosubs, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("a([bc]?)c", perl, "abc", match_default|match_nosubs, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a([bc]?)c", perl, "ac", match_default|match_nosubs, make_array(0, 2, -2, -2));

   TEST_REGEX_SEARCH("a([bc]+)c", perl, "abc", match_default|match_nosubs, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a([bc]+)c", perl, "abcc", match_default|match_nosubs, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("a([bc]+)bc", perl, "abcbc", match_default|match_nosubs, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("a(bb+|b)b", perl, "abb", match_default|match_nosubs, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a(bbb+|bb+|b)b", perl, "abb", match_default|match_nosubs, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a(bbb+|bb+|b)b", perl, "abbb", match_default|match_nosubs, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("a(bbb+|bb+|b)bb", perl, "abbb", match_default|match_nosubs, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("(.*).*", perl, "abcdef", match_default|match_nosubs, make_array(0, 6, -2, 6, 6, -2, -2));
   TEST_REGEX_SEARCH("(a*)*", perl, "bc", match_default|match_nosubs, make_array(0, 0, -2, 1, 1, -2, 2, 2, -2, -2));

   TEST_REGEX_SEARCH("a(b?c)+d", perl|nosubs, "accd", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("(wee|week)(knights|night)", perl|nosubs, "weeknights", match_default, make_array(0, 10, -2, -2));
   TEST_REGEX_SEARCH(".*", perl|nosubs, "abc", match_default, make_array(0, 3, -2, 3, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b|(c))d", perl|nosubs, "abd", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b|(c))d", perl|nosubs, "acd", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b*|c|e)d", perl|nosubs, "abbd", match_default, make_array(0, 4, -2, -2));
   
   TEST_REGEX_SEARCH("a(b*|c|e)d", perl|nosubs, "acd", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b*|c|e)d", perl|nosubs, "ad", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a(b?)c", perl|nosubs, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b?)c", perl|nosubs, "ac", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("a(b+)c", perl|nosubs, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a(b+)c", perl|nosubs, "abbbc", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("a(b*)c", perl|nosubs, "ac", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("(a|ab)(bc([de]+)f|cde)", perl|nosubs, "abcdef", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH("a([bc]?)c", perl|nosubs, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a([bc]?)c", perl|nosubs, "ac", match_default, make_array(0, 2, -2, -2));

   TEST_REGEX_SEARCH("a([bc]+)c", perl|nosubs, "abc", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a([bc]+)c", perl|nosubs, "abcc", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("a([bc]+)bc", perl|nosubs, "abcbc", match_default, make_array(0, 5, -2, -2));
   TEST_REGEX_SEARCH("a(bb+|b)b", perl|nosubs, "abb", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a(bbb+|bb+|b)b", perl|nosubs, "abb", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("a(bbb+|bb+|b)b", perl|nosubs, "abbb", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("a(bbb+|bb+|b)bb", perl|nosubs, "abbb", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("(.*).*", perl|nosubs, "abcdef", match_default, make_array(0, 6, -2, 6, 6, -2, -2));
   TEST_REGEX_SEARCH("(a*)*", perl|nosubs, "bc", match_default, make_array(0, 0, -2, 1, 1, -2, 2, 2, -2, -2));
}

void test_conditionals()
{
   using namespace boost::regex_constants;
   TEST_REGEX_SEARCH("(?:(a)|b)(?(1)A|B)", perl, "aA", match_default, make_array(0, 2, 0, 1, -2, -2));
   TEST_REGEX_SEARCH("(?:(a)|b)(?(1)A|B)", perl, "bB", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("(?:(a)|b)(?(1)A|B)", perl, "aB", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("(?:(a)|b)(?(1)A|B)", perl, "bA", match_default, make_array(-2, -2));

   TEST_REGEX_SEARCH("^(a)?(?(1)a|b)+$", perl, "aa", match_default, make_array(0, 2, 0, 1, -2, -2));
   TEST_REGEX_SEARCH("^(a)?(?(1)a|b)+$", perl, "b", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("^(a)?(?(1)a|b)+$", perl, "bb", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("^(a)?(?(1)a|b)+$", perl, "ab", match_default, make_array(-2, -2));

   TEST_REGEX_SEARCH("^(?(?=abc)\\w{3}:|\\d\\d)$", perl, "abc:", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("^(?(?=abc)\\w{3}:|\\d\\d)$", perl, "12", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("^(?(?=abc)\\w{3}:|\\d\\d)$", perl, "123", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("^(?(?=abc)\\w{3}:|\\d\\d)$", perl, "xyz", match_default, make_array(-2, -2));

   TEST_REGEX_SEARCH("^(?(?!abc)\\d\\d|\\w{3}:)$", perl, "abc:", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("^(?(?!abc)\\d\\d|\\w{3}:)$", perl, "12", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("^(?(?!abc)\\d\\d|\\w{3}:)$", perl, "123", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("^(?(?!abc)\\d\\d|\\w{3}:)$", perl, "xyz", match_default, make_array(-2, -2));

   TEST_REGEX_SEARCH("(?(?<=foo)bar|cat)", perl, "foobar", match_default, make_array(3, 6, -2, -2));
   TEST_REGEX_SEARCH("(?(?<=foo)bar|cat)", perl, "cat", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("(?(?<=foo)bar|cat)", perl, "fcat", match_default, make_array(1, 4, -2, -2));
   TEST_REGEX_SEARCH("(?(?<=foo)bar|cat)", perl, "focat", match_default, make_array(2, 5, -2, -2));
   TEST_REGEX_SEARCH("(?(?<=foo)bar|cat)", perl, "foocat", match_default, make_array(-2, -2));

   TEST_REGEX_SEARCH("(?(?<!foo)cat|bar)", perl, "foobar", match_default, make_array(3, 6, -2, -2));
   TEST_REGEX_SEARCH("(?(?<!foo)cat|bar)", perl, "cat", match_default, make_array(0, 3, -2, -2));
   TEST_REGEX_SEARCH("(?(?<!foo)cat|bar)", perl, "fcat", match_default, make_array(1, 4, -2, -2));
   TEST_REGEX_SEARCH("(?(?<!foo)cat|bar)", perl, "focat", match_default, make_array(2, 5, -2, -2));
   TEST_REGEX_SEARCH("(?(?<!foo)cat|bar)", perl, "foocat", match_default, make_array(-2, -2));

   TEST_REGEX_SEARCH("(\\()?[^()]+(?(1)\\))", perl, "abcd", match_default, make_array(0, 4, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("(\\()?[^()]+(?(1)\\))", perl, "(abcd)", match_default, make_array(0, 6, 0, 1, -2, -2));
   TEST_REGEX_SEARCH("(\\()?[^()]+(?(1)\\))", perl, "the quick (abcd) fox", match_default, make_array(0, 10, -1, -1, -2, 10, 16, 10, 11, -2, 16, 20, -1, -1, -2, -2));
   TEST_REGEX_SEARCH("(\\()?[^()]+(?(1)\\))", perl, "(abcd", match_default, make_array(1, 5, -1, -1, -2, -2));

   TEST_REGEX_SEARCH("^(?(2)a|(1)(2))+$", perl, "12", match_default, make_array(0, 2, 0, 1, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("^(?(2)a|(1)(2))+$", perl, "12a", match_default, make_array(0, 3, 0, 1, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("^(?(2)a|(1)(2))+$", perl, "12aa", match_default, make_array(0, 4, 0, 1, 1, 2, -2, -2));
   TEST_REGEX_SEARCH("^(?(2)a|(1)(2))+$", perl, "1234", match_default, make_array(-2, -2));

   //TEST_REGEX_SEARCH("", perl, "", match_default, make_array(-2, -2));

#if 0
#endif
}
