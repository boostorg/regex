

#include "test.hpp"

void basic_tests()
{
   using namespace boost::regex_constants;
   TEST_REGEX_SEARCH("a", basic, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("a", basic, "bba", match_default, make_array(2, 3, -2, -2));
   TEST_REGEX_SEARCH("Z", perl, "aaa", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH("Z", perl, "xxxxZZxxx", match_default, make_array(4, 5, -2, 5, 6, -2, -2));
   // and some simple brackets:
   TEST_REGEX_SEARCH("(a)", perl, "zzzaazz", match_default, make_array(3, 4, 3, 4, 4, 5, 4, 5, -2, -2));
   TEST_REGEX_SEARCH("()", perl, "zzz", match_default, make_array(0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, -2, -2));
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
   //TEST_REGEX_SEARCH("[pq](a)rameter", perl, "ABCparameterXYZ", match_default, make_array(3, 12, 4, 5, -2, -2));

   // now try escaped brackets:
   TEST_REGEX_SEARCH("\\(a\\)", basic, "zzzaazz", match_default, make_array(3, 4, 3, 4, 4, 5, 4, 5, -2, -2));
   TEST_REGEX_SEARCH("\\(\\)", basic, "zzz", match_default, make_array(0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, -2, -2));
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
   //TEST_REGEX_SEARCH("[pq]\\(a\\)rameter", basic, "ABCparameterXYZ", match_default, make_array(3, 12, 4, 5, -2, -2));

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
   TEST_REGEX_SEARCH("a*", perl, "b", match_default, make_array(0, 0, -2, -2));
   TEST_REGEX_SEARCH("ab*", perl, "ab", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("ab*", perl, "sssabbbbbbsss", match_default, make_array(3, 10, -2, -2));
   TEST_REGEX_SEARCH("ab*c*", perl, "a", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("ab*c*", perl, "abbb", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab*c*", perl, "accc", match_default, make_array(0, 4, -2, -2));
   TEST_REGEX_SEARCH("ab*c*", perl, "abbcc", match_default, make_array(0, 5, -2, -2));
   TEST_INVALID_REGEX("*a", perl);
   TEST_INVALID_REGEX("\\<*", perl);
   TEST_INVALID_REGEX("\\>*", perl);
   TEST_REGEX_SEARCH("\n*", perl, "\n\n", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("\\**", perl, "**", match_default, make_array(0, 2, -2, -2));
   TEST_REGEX_SEARCH("\\*", perl, "*", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("(ab)*", perl, "abab", match_default, make_array(0, 4, 2, 4, -2, -2));

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
   TEST_REGEX_SEARCH("a?", perl, "b", match_default, make_array(0, 0, -2, -2));
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
   TEST_REGEX_SEARCH("\n?", perl, "\n\n", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\?", perl, "?", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\?", perl, "?", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("\\??", perl, "??", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("?", basic|bk_plus_qm, "?", match_default, make_array(0, 1, -2, -2));
   TEST_INVALID_REGEX("\\?", basic|bk_plus_qm);
   TEST_REGEX_SEARCH("a\\?", basic|bk_plus_qm, "aa", match_default, make_array(0, 1, -2, -2));
   TEST_REGEX_SEARCH("a\\?", basic|bk_plus_qm, "b", match_default, make_array(0, 0, -2, -2));

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
   TEST_REGEX_SEARCH("(ab*)[ab]*\\1", perl, "ababaaa", match_default, make_array(0, 4, 0, 2, -2, -2));
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
}

void test_tricky_cases()
{
   using namespace boost::regex_constants;
   //TEST_REGEX_SEARCH("", perl, "", match_default, make_array(-2, -2));
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
   TEST_REGEX_SEARCH(".*", perl, "abc", match_default, make_array(0, 3, -2, -2));
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
   TEST_REGEX_SEARCH("(.*).*", perl, "abcdef", match_default, make_array(0, 6, 0, 6, -2, -2));
   TEST_REGEX_SEARCH("(a*)*", perl, "bc", match_default, make_array(0, 0, 0, 0, -2, -2));
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
   TEST_REGEX_SEARCH_W(L"[[:unicode:]]+", perl, L"a\u0300\u0400z", match_default, make_array(1, 3, -2, -2));
   TEST_REGEX_SEARCH_W(L"[\x10-\xff]", perl, L"\u0300\u0400", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH_W(L"[\01-\05]{5}", perl, L"\u0300\u0400\u0300\u0400\u0300\u0400", match_default, make_array(-2, -2));
   TEST_REGEX_SEARCH_W(L"[\x300-\x400]+", perl, L"\u0300\u0400\u0300\u0400\u0300\u0400", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH_W(L"[\\x{300}-\\x{400}]+", perl, L"\u0300\u0400\u0300\u0400\u0300\u0400", match_default, make_array(0, 6, -2, -2));
   TEST_REGEX_SEARCH_W(L"\\x{300}\\x{400}+", perl, L"\u0300\u0400\u0400\u0400\u0400\u0400", match_default, make_array(0, 6, -2, -2));
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
#if 0
; collating elements and rewritten set code:
- match_default normal REG_EXTENDED REG_STARTEND
[[.zero.]] 0 0 1
[[.one.]] 1 0 1
[[.two.]] 2 0 1
[[.three.]] 3 0 1
[[.a.]] baa 1 2
[[.right-curly-bracket.]] } 0 1
[[.NUL.]] \0 0 1
[[:<:]z] !
[a[:>:]] !
[[=a=]] a 0 1
[[=right-curly-bracket=]] } 0 1
- match_default normal REG_EXTENDED REG_STARTEND REG_ICASE
[[.A.]] A 0 1
[[.A.]] a 0 1
[[.A.]-b]+ AaBb 0 4
[A-[.b.]]+ AaBb 0 4
[[.a.]-B]+ AaBb 0 4
[a-[.B.]]+ AaBb 0 4
- match_default normal REG_EXTENDED REG_NO_POSIX_TEST
[\x61] a 0 1
[\x61-c]+ abcd 0 3
[a-\x63]+ abcd 0 3
- match_default normal REG_EXTENDED REG_STARTEND
[[.a.]-c]+ abcd 0 3
[a-[.c.]]+ abcd 0 3
[[:alpha:]-a] !
[a-[:alpha:]] !

; try mutli-character ligatures:
[[.ae.]] ae 0 2
[[.ae.]] aE -1 -1
[[.AE.]] AE 0 2
[[.Ae.]] Ae 0 2
[[.ae.]-b] a -1 -1
[[.ae.]-b] b 0 1
[[.ae.]-b] ae 0 2
[a-[.ae.]] a 0 1
[a-[.ae.]] b -1 -1
[a-[.ae.]] ae 0 2
- match_default normal REG_EXTENDED REG_STARTEND REG_ICASE
[[.ae.]] AE 0 2
[[.ae.]] Ae 0 2
[[.AE.]] Ae 0 2
[[.Ae.]] aE 0 2
[[.AE.]-B] a -1 -1
[[.Ae.]-b] b 0 1
[[.Ae.]-b] B 0 1
[[.ae.]-b] AE 0 2

- match_default normal REG_EXTENDED REG_STARTEND
;extended perl style escape sequences:
\e \27 0 1
\x1b \27 0 1
\x{1b} \27 0 1
\x{} !
\x{ !
\x} !
\x !
\x{yy !
\x{1b !

- match_default normal REG_EXTENDED REG_STARTEND REG_NO_POSIX_TEST
\l+ ABabcAB 2 5
[\l]+ ABabcAB 2 5
[a-\l] !
[\l-a] !
[\L] !
\L+ abABCab 2 5
\u+ abABCab 2 5
[\u]+ abABCab 2 5
[\U] !
\U+ ABabcAB 2 5
\d+ ab012ab 2 5
[\d]+ ab012ab 2 5
[\D] !
\D+ 01abc01 2 5
\s+ "ab   ab" 2 5
[\s]+ "ab   ab" 2 5
[\S] !
\S+ "  abc  " 2 5
- match_default normal REG_EXTENDED REG_STARTEND
\Qabc !
\Qabc\E abcd 0 3
\Qabc\Ed abcde 0 4
\Q+*?\\E +*?\\ 0 4

\C+ abcde 0 5
\X+ abcde 0 5

- match_default normal REG_EXTENDED REG_STARTEND REG_UNICODE_ONLY
\X+ a\768\769 0 3
\X+ \2309\2307 0 2   ;DEVANAGARI script
\X+ \2489\2494 0 2   ;BENGALI script

- match_default normal REG_EXTENDED REG_STARTEND
\Aabc abc 0 3
\Aabc aabc -1 -1
abc\z abc 0 3
abc\z abcd -1 -1
abc\Z abc\n\n 0 3
abc\Z abc 0 3


\Gabc abc 0 3
\Gabc dabcd -1 -1
a\Gbc abc -1 -1
a\Aab abc -1 -1

;
; now test grep,
; basically check all our restart types - line, word, etc
; checking each one for null and non-null matches.
;
- match_default normal REG_EXTENDED REG_STARTEND REG_GREP
a " a a a aa" 1 2 3 4 5 6 7 8 8 9
a+b+ "aabaabbb ab" 0 3 3 8 9 11
a(b*|c|e)d adabbdacd 0 2 2 6 6 9
a "\na\na\na\naa" 1 2 3 4 5 6 7 8 8 9

^ "   \n\n  \n\n\n" 0 0 4 4 5 5 8 8 9 9 10 10
^ab  "ab  \nab  ab\n" 0 2 5 7
^[^\n]*\n "   \n  \n\n  \n" 0 4 4 7 7 8 8 11
\<abc "abcabc abc\n\nabc" 0 3 7 10 12 15
\< "  ab a aaa  "  2 2 5 5 7 7
\<\w+\W+ " aa  aa  a " 1 5 5 9 9 11

\Aabc "abc   abc"  0 3
\G\w+\W+ "abc  abc a cbbb   " 0 5 5 9 9 11 11 18
\Ga+b+ "aaababb  abb" 0 4 4 7

abc abc 0 3
abc " abc abcabc " 1 4 5 8 8 11
\n\n " \n\n\n       \n      \n\n\n\n  " 1 3 18 20 20 22

$ "   \n\n  \n\n\n" 3 3 4 4 7 7 8 8 9 9 10 10
\b "  abb a abbb " 2 2 5 5 6 6 7 7 8 8 12 12

- match_default normal REG_EXTENDED REG_STARTEND REG_GREP REG_ICASE
A " a a a aa" 1 2 3 4 5 6 7 8 8 9
A+B+ "aabaabbb ab" 0 3 3 8 9 11
A(B*|c|e)D adabbdacd 0 2 2 6 6 9
A "\na\na\na\naa" 1 2 3 4 5 6 7 8 8 9

^aB  "Ab  \nab  Ab\n" 0 2 5 7
\<abc "Abcabc aBc\n\nabc" 0 3 7 10 12 15

ABC abc 0 3
abc " ABC ABCABC " 1 4 5 8 8 11


;
; now test merge,
;
- match_default normal REG_EXTENDED REG_STARTEND REG_MERGE format_no_copy
; start by testing subs:
a+ "...aaa,,," $` "..." 
a+ "...aaa,,," $' ",,," 
a+ "...aaa,,," $& "aaa" 
a+ "...aaa,,," $0 aaa
a+ "...aaa,,," $1 ""
a+ "...aaa,,," $15 ""
(a+)b+ "...aaabbb,,," $1 aaa
[[:digit:]]* 123ab <$0> <123><><><>
[[:digit:]]* 123ab1 <$0> <123><><><1>

; and now escapes:
a+ "...aaa,,," $x "$x" 
a+ "...aaa,,," \a "\a" 
a+ "...aaa,,," \f "\f" 
a+ "...aaa,,," \n "\n" 
a+ "...aaa,,," \r "\r" 
a+ "...aaa,,," \t "\t" 
a+ "...aaa,,," \v "\v" 

a+ "...aaa,,," \x21 "!" 
a+ "...aaa,,," \x{21} "!" 
a+ "...aaa,,," \c@ \0
a+ "...aaa,,," \e \27
a+ "...aaa,,," \0101 A

- match_default normal REG_EXTENDED REG_STARTEND REG_MERGE format_sed format_no_copy
(a+)(b+) ...aabb,, \0 aabb
(a+)(b+) ...aabb,, \1 aa
(a+)(b+) ...aabb,, \2 bb
(a+)(b+) ...aabb,, & aabb
(a+)(b+) ...aabb,, $ $
(a+)(b+) ...aabb,, $1 $1
(a+)(b+) ...aabb,, ()?: ()?:
(a+)(b+) ...aabb,, \\ \\
(a+)(b+) ...aabb,, \& &


- match_default normal REG_EXTENDED REG_STARTEND REG_MERGE format_perl format_no_copy
(a+)(b+) ...aabb,, $0 aabb
(a+)(b+) ...aabb,, $1 aa
(a+)(b+) ...aabb,, $2 bb
(a+)(b+) ...aabb,, $& aabb
(a+)(b+) ...aabb,, & &
(a+)(b+) ...aabb,, \0 \0
(a+)(b+) ...aabb,, ()?: ()?:
a+ "...aaa,,," \0101 A

- match_default format_all normal REG_EXTENDED REG_STARTEND REG_MERGE
; move to copying unmatched data:
a+ "...aaa,,," bbb "...bbb,,," 
a+(b+) "...aaabb,,," $1 "...bb,,," 
a+(b+) "...aaabb,,,ab*abbb?" $1 "...bb,,,b*bbb?" 

(a+)|(b+) "...aaabb,,,ab*abbb?" (?1A)(?2B) "...AB,,,AB*AB?" 
(a+)|(b+) "...aaabb,,,ab*abbb?" ?1A:B "...AB,,,AB*AB?" 
(a+)|(b+) "...aaabb,,,ab*abbb?" (?1A:B)C "...ACBC,,,ACBC*ACBC?" 
(a+)|(b+) "...aaabb,,,ab*abbb?" ?1:B "...B,,,B*B?" 

- match_default format_all normal REG_EXTENDED REG_STARTEND REG_MERGE format_first_only
; move to copying unmatched data, but replace first occurance only:
a+ "...aaa,,," bbb "...bbb,,," 
a+(b+) "...aaabb,,," $1 "...bb,,," 
a+(b+) "...aaabb,,,ab*abbb?" $1 "...bb,,,ab*abbb?" 
(a+)|(b+) "...aaabb,,,ab*abbb?" (?1A)(?2B) "...Abb,,,ab*abbb?" 

;
; changes to newline handling with 2.11:
;

- match_default normal REG_EXTENDED REG_STARTEND REG_GREP

^. "  \n  \r\n  " 0 1 3 4 7 8
.$ "  \n  \r\n  " 1 2 4 5 8 9

- match_default normal REG_EXTENDED REG_STARTEND REG_GREP REG_UNICODE_ONLY
^. "  \8232 \8233  " 0 1 3 4 5 6
.$ "  \8232 \8233  " 1 2 3 4 6 7

;
; non-greedy repeats added 21/04/00
- match_default normal REG_EXTENDED REG_PERL
a** !
a*? aa 0 0
^a*?$ aa 0 2
^.*?$ aa 0 2
^(?:a)*?$ aa 0 2
^[ab]*?$ aa 0 2
a?? aa 0 0
a++ !
a+? aa 0 1
a{1,3}{1} !
a{1,3}? aaa 0 1
\w+?w ...ccccccwcccccw 3 10
\W+\w+?w ...ccccccwcccccw 0 10
abc|\w+? abd 0 1
abc|\w+? abcd 0 3
<\s*tag[^>]*>(.*?)<\s*/tag\s*> " <tag>here is some text</tag> <tag></tag>" 1 29 6 23
<\s*tag[^>]*>(.*?)<\s*/tag\s*> " < tag attr=\"something\">here is some text< /tag > <tag></tag>" 1 49 24 41

;
; non-marking parenthesis added 25/04/00
- match_default normal REG_EXTENDED REG_PERL
(?:abc)+ xxabcabcxx 2 8
(?:a+)(b+) xaaabbbx 1 7 4 7
(a+)(?:b+) xaaabbba 1 7 1 4
(?:(a+)b+) xaaabbba 1 7 1 4
(?:a+(b+)) xaaabbba 1 7 4 7
a+(?#b+)b+ xaaabbba 1 7
(a)(?:b|$) ab 0 2 0 1
(a)(?:b|$) a 0 1 0 1


;
; try some partial matches:
- match_partial match_default normal REG_EXTENDED REG_NO_POSIX_TEST REG_PARTIAL_MATCH REG_PERL
(xyz)(.*)abc xyzaaab 0 7
(xyz)(.*)abc xyz 0 3
(xyz)(.*)abc xy 0 2
(xyz)(.*)abc x 0 1
(xyz)(.*)abc "" -1 -1
(xyz)(.*)abc aaaa -1 -1
.abc aaab 1 4
a[_] xxa 2 3

;
; forward lookahead asserts added 21/01/02
- match_default normal REG_EXTENDED REG_NO_POSIX_TEST REG_PERL
((?:(?!a|b)\w)+)(\w+) "  xxxabaxxx  " 2 11 2 5 5 11

/\*(?:(?!\*/).)*\*/ "  /**/  " 2 6
/\*(?:(?!\*/).)*\*/ "  /***/  " 2 7
/\*(?:(?!\*/).)*\*/ "  /********/  " 2 12
/\*(?:(?!\*/).)*\*/ "  /* comment */  " 2 15

<\s*a[^>]*>((?:(?!<\s*/\s*a\s*>).)*)<\s*/\s*a\s*> " <a href=\"here\">here</a> " 1 24 16 20
<\s*a[^>]*>((?:(?!<\s*/\s*a\s*>).)*)<\s*/\s*a\s*> " <a href=\"here\">here< /  a > " 1 28 16 20

<\s*a[^>]*>((?:(?!<\s*/\s*a\s*>).)*)(?=<\s*/\s*a\s*>) " <a href=\"here\">here</a> " 1 20 16 20
<\s*a[^>]*>((?:(?!<\s*/\s*a\s*>).)*)(?=<\s*/\s*a\s*>) " <a href=\"here\">here< /  a > " 1 20 16 20

; filename matching:
^(?!^(?:PRN|AUX|CLOCK\$|NUL|CON|COM\d|LPT\d|\..*)(?:\..+)?$)[^\x00-\x1f\\?*:\"|/]+$ command.com 0 11
^(?!^(?:PRN|AUX|CLOCK\$|NUL|CON|COM\d|LPT\d|\..*)(?:\..+)?$)[^\x00-\x1f\\?*:\"|/]+$ PRN -1 -1
^(?!^(?:PRN|AUX|CLOCK\$|NUL|CON|COM\d|LPT\d|\..*)(?:\..+)?$)[^\x00-\x1f\\?*:\"|/]+$ COM2 -1 -1

; password checking:
^(?=.*\d).{4,8}$ abc3 0 4
^(?=.*\d).{4,8}$ abc3def4 0 8
^(?=.*\d).{4,8}$ ab2 -1 -1
^(?=.*\d).{4,8}$ abcdefg -1 -1
^(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{4,8}$ abc3 -1 -1
^(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{4,8}$ abC3 0 4
^(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{4,8}$ ABCD3 -1 -1

; extended repeat checking to exercise new algorithms:
ab.*xy abxy_ 0 4
ab.*xy ab_xy_ 0 5
ab.*xy abxy 0 4
ab.*xy ab_xy 0 5
ab.* ab 0 2
ab.* ab__ 0 4

ab.{2,5}xy ab__xy_ 0 6
ab.{2,5}xy ab____xy_ 0 8
ab.{2,5}xy ab_____xy_ 0 9
ab.{2,5}xy ab__xy 0 6
ab.{2,5}xy ab_____xy 0 9
ab.{2,5} ab__ 0 4
ab.{2,5} ab_______ 0 7
ab.{2,5}xy ab______xy -1 -1
ab.{2,5}xy ab_xy -1 -1

ab.*?xy abxy_ 0 4
ab.*?xy ab_xy_ 0 5
ab.*?xy abxy 0 4
ab.*?xy ab_xy 0 5
ab.*? ab 0 2
ab.*? ab__ 0 2

ab.{2,5}?xy ab__xy_ 0 6
ab.{2,5}?xy ab____xy_ 0 8
ab.{2,5}?xy ab_____xy_ 0 9
ab.{2,5}?xy ab__xy 0 6
ab.{2,5}?xy ab_____xy 0 9
ab.{2,5}? ab__ 0 4
ab.{2,5}? ab_______ 0 4
ab.{2,5}?xy ab______xy -1 -1
ab.{2,5}xy ab_xy -1 -1

; again but with slower algorithm variant:
- match_default normal REG_PERL REG_NO_POSIX_TEST match_not_dot_newline match_not_dot_null
ab.*xy abxy_ 0 4
ab.*xy ab_xy_ 0 5
ab.*xy abxy 0 4
ab.*xy ab_xy 0 5
ab.* ab 0 2
ab.* ab__ 0 4

ab.{2,5}xy ab__xy_ 0 6
ab.{2,5}xy ab____xy_ 0 8
ab.{2,5}xy ab_____xy_ 0 9
ab.{2,5}xy ab__xy 0 6
ab.{2,5}xy ab_____xy 0 9
ab.{2,5} ab__ 0 4
ab.{2,5} ab_______ 0 7
ab.{2,5}xy ab______xy -1 -1
ab.{2,5}xy ab_xy -1 -1

ab.*?xy abxy_ 0 4
ab.*?xy ab_xy_ 0 5
ab.*?xy abxy 0 4
ab.*?xy ab_xy 0 5
ab.*? ab 0 2
ab.*? ab__ 0 2

ab.{2,5}?xy ab__xy_ 0 6
ab.{2,5}?xy ab____xy_ 0 8
ab.{2,5}?xy ab_____xy_ 0 9
ab.{2,5}?xy ab__xy 0 6
ab.{2,5}?xy ab_____xy 0 9
ab.{2,5}? ab__ 0 4
ab.{2,5}? ab_______ 0 4
ab.{2,5}?xy ab______xy -1 -1
ab.{2,5}xy ab_xy -1 -1
(.*?).somesite \n\n555.somesite 2 14 2 5

; now again for single character repeats:

ab_*xy abxy_ 0 4
ab_*xy ab_xy_ 0 5
ab_*xy abxy 0 4
ab_*xy ab_xy 0 5
ab_* ab 0 2
ab_* ab__ 0 4

ab_{2,5}xy ab__xy_ 0 6
ab_{2,5}xy ab____xy_ 0 8
ab_{2,5}xy ab_____xy_ 0 9
ab_{2,5}xy ab__xy 0 6
ab_{2,5}xy ab_____xy 0 9
ab_{2,5} ab__ 0 4
ab_{2,5} ab_______ 0 7
ab_{2,5}xy ab______xy -1 -1
ab_{2,5}xy ab_xy -1 -1

ab_*?xy abxy_ 0 4
ab_*?xy ab_xy_ 0 5
ab_*?xy abxy 0 4
ab_*?xy ab_xy 0 5
ab_*? ab 0 2
ab_*? ab__ 0 2

ab_{2,5}?xy ab__xy_ 0 6
ab_{2,5}?xy ab____xy_ 0 8
ab_{2,5}?xy ab_____xy_ 0 9
ab_{2,5}?xy ab__xy 0 6
ab_{2,5}?xy ab_____xy 0 9
ab_{2,5}? ab__ 0 4
ab_{2,5}? ab_______ 0 4
ab_{2,5}?xy ab______xy -1 -1
ab_{2,5}xy ab_xy -1 -1
(5*?).somesite //555.somesite 2 14 2 5

; and again for sets:
ab[_,;]*xy abxy_ 0 4
ab[_,;]*xy ab_xy_ 0 5
ab[_,;]*xy abxy 0 4
ab[_,;]*xy ab_xy 0 5
ab[_,;]* ab 0 2
ab[_,;]* ab__ 0 4

ab[_,;]{2,5}xy ab__xy_ 0 6
ab[_,;]{2,5}xy ab____xy_ 0 8
ab[_,;]{2,5}xy ab_____xy_ 0 9
ab[_,;]{2,5}xy ab__xy 0 6
ab[_,;]{2,5}xy ab_____xy 0 9
ab[_,;]{2,5} ab__ 0 4
ab[_,;]{2,5} ab_______ 0 7
ab[_,;]{2,5}xy ab______xy -1 -1
ab[_,;]{2,5}xy ab_xy -1 -1

ab[_,;]*?xy abxy_ 0 4
ab[_,;]*?xy ab_xy_ 0 5
ab[_,;]*?xy abxy 0 4
ab[_,;]*?xy ab_xy 0 5
ab[_,;]*? ab 0 2
ab[_,;]*? ab__ 0 2

ab[_,;]{2,5}?xy ab__xy_ 0 6
ab[_,;]{2,5}?xy ab____xy_ 0 8
ab[_,;]{2,5}?xy ab_____xy_ 0 9
ab[_,;]{2,5}?xy ab__xy 0 6
ab[_,;]{2,5}?xy ab_____xy 0 9
ab[_,;]{2,5}? ab__ 0 4
ab[_,;]{2,5}? ab_______ 0 4
ab[_,;]{2,5}?xy ab______xy -1 -1
ab[_,;]{2,5}xy ab_xy -1 -1
(\d*?).somesite //555.somesite 2 14 2 5

; and again for tricky sets with digraphs:
ab[_[.ae.]]*xy abxy_ 0 4
ab[_[.ae.]]*xy ab_xy_ 0 5
ab[_[.ae.]]*xy abxy 0 4
ab[_[.ae.]]*xy ab_xy 0 5
ab[_[.ae.]]* ab 0 2
ab[_[.ae.]]* ab__ 0 4

ab[_[.ae.]]{2,5}xy ab__xy_ 0 6
ab[_[.ae.]]{2,5}xy ab____xy_ 0 8
ab[_[.ae.]]{2,5}xy ab_____xy_ 0 9
ab[_[.ae.]]{2,5}xy ab__xy 0 6
ab[_[.ae.]]{2,5}xy ab_____xy 0 9
ab[_[.ae.]]{2,5} ab__ 0 4
ab[_[.ae.]]{2,5} ab_______ 0 7
ab[_[.ae.]]{2,5}xy ab______xy -1 -1
ab[_[.ae.]]{2,5}xy ab_xy -1 -1

ab[_[.ae.]]*?xy abxy_ 0 4
ab[_[.ae.]]*?xy ab_xy_ 0 5
ab[_[.ae.]]*?xy abxy 0 4
ab[_[.ae.]]*?xy ab_xy 0 5
ab[_[.ae.]]*? ab 0 2
ab[_[.ae.]]*? ab__ 0 2

ab[_[.ae.]]{2,5}?xy ab__xy_ 0 6
ab[_[.ae.]]{2,5}?xy ab____xy_ 0 8
ab[_[.ae.]]{2,5}?xy ab_____xy_ 0 9
ab[_[.ae.]]{2,5}?xy ab__xy 0 6
ab[_[.ae.]]{2,5}?xy ab_____xy 0 9
ab[_[.ae.]]{2,5}? ab__ 0 4
ab[_[.ae.]]{2,5}? ab_______ 0 4
ab[_[.ae.]]{2,5}?xy ab______xy -1 -1
ab[_[.ae.]]{2,5}xy ab_xy -1 -1
([5[.ae.]]*?).somesite //555.somesite 2 14 2 5

; new bugs detected in spring 2003:
- normal match_continuous REG_NO_POSIX_TEST
b abc -1 -1

- normal REG_PERL
(?!foo)bar foobar 3 6
(?!foo)bar "??bar" 2 5
(?!foo)bar "barfoo" 0 3
(?!foo)bar "bar??" 0 3
(?!foo)bar bar 0 3

a\Z a\nb -1 -1
() abc 0 0 0 0
^() abc 0 0 0 0
^()+ abc 0 0 0 0
^(){1} abc 0 0 0 0
^(){2} abc 0 0 0 0
^((){2}) abc 0 0 0 0 0 0
() "" 0 0 0 0
()\1 "" 0 0 0 0
()\1 a 0 0 0 0
a()\1b ab 0 2 1 1
a()b\1 ab 0 2 1 1

- normal match_not_dot_newline REG_NO_POSIX_TEST

"(.*\r\n){3}.* abcdefghijklmnopqrstuvwxyz.*\r\n" "00001 01 \r\n00002 02 1         2         3         4         5         6         7         8         9         0\r\n00003 03 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\r\n00004 04 \r\n00005 05 \r\n00006 06                                                             Seite: 0001\r\n00007 07                                                             StartSeitEEnde: 0001\r\n00008 08                                                             StartSeiTe Ende: 0001\r\n00009 09                                                             Start seiteEnde: 0001\r\n00010 10                                                             28.2.03\r\n00011 11                                                             Page: 0001\r\n00012 12                                                             Juhu die Erste: 0001\r\n00013 13                                                             Es war einmal! 0001\r\n00014 14      

- normal REG_PERL

; new (?: construct )
(?>^abc) abc 0 3
(?>^abc) def\nabc 4 7
(?>^abc) defabc -1 -1
(?>.*/)foo /this/is/a/very/long/line/in/deed/with/very/many/slashes/in/it/you/see/ -1 -1
(?>.*/)foo /this/is/a/very/long/line/in/deed/with/very/many/slashes/in/and/foo 0 67
(?>(\.\d\d[1-9]?))\d+ 1.230003938 1 11 1 4
(?>(\.\d\d[1-9]?))\d+ 1.875000282 1 11 1 5
(?>(\.\d\d[1-9]?))\d+ 1.235 -1 -1
^((?>\w+)|(?>\s+))*$ "now is the time for all good men to come to the aid of the party" 0 64 59 64
^((?>\w+)|(?>\s+))*$ "this is not a line with only words and spaces!" -1 -1
((?>\d+))(\w) 12345a 0 6 0 5 5 6
((?>\d+))(\w) 12345+ -1 -1
((?>\d+))(\d) 12345 -1 -1
(?>a+)b aaab 0 4
((?>a+)b) aaab 0 4 0 4
(?>(a+))b aaab 0 4 0 3
(?>b)+ aaabbbccc 3 6
(?>a+|b+|c+)*c aaabbbbccccd 0 8
((?>[^()]+)|\([^()]*\))+ ((abc(ade)ufh()()x 2 18 17 18
\(((?>[^()]+)|\([^()]+\))+\) (abc) 0 5 1 4
\(((?>[^()]+)|\([^()]+\))+\) (abc(def)xyz) 0 13 9 12
\(((?>[^()]+)|\([^()]+\))+\) ((()aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa -1 -1
(?>a*)* a 0 1
(?>a*)* aa 0 2
(?>a*)* aaaa 0 4
(?>a*)* a 0 1
(?>a*)* aaabcde 0 3
((?>a*))* aaaaa 0 5 5 5
((?>a*))* aabbaa 0 2 2 2
((?>a*?))* aaaaa 0 0 0 0
((?>a*?))*    aabbaa 0 0 0 0
"word (?>(?:(?!otherword)[a-zA-Z0-9]+ ){0,30})otherword" "word cat dog elephant mussel cow horse canary baboon snake shark otherword" 0 74
"word (?>(?:(?!otherword)[a-zA-Z0-9]+ ){0,30})otherword" "word cat dog elephant mussel cow horse canary baboon snake shark" -1 -1
"word (?>[a-zA-Z0-9]+ ){0,30}otherword" "word cat dog elephant mussel cow horse canary baboon snake shark the quick brown fox and the lazy dog and several other words getting close to thirty by now I hope" -1 -1
"word (?>[a-zA-Z0-9]+ ){0,30}otherword" "word cat dog elephant mussel cow horse canary baboon snake shark the quick brown fox and the lazy dog and several other words getting close to thirty by now I really really hope otherword" -1 -1
((?>Z)+|A)* ZABCDEFG 0 2 1 2
((?>)+|A)* !

; subtleties of matching with no sub-expressions marked
- normal match_nosubs REG_NO_POSIX_TEST
a(b?c)+d accd 0 4 
(wee|week)(knights|night) weeknights 0 10 
.* abc 0 3
a(b|(c))d abd 0 3 
a(b|(c))d acd 0 3
a(b*|c|e)d abbd 0 4
a(b*|c|e)d acd 0 3 
a(b*|c|e)d ad 0 2
a(b?)c abc 0 3
a(b?)c ac 0 2
a(b+)c abc 0 3
a(b+)c abbbc 0 5
a(b*)c ac 0 2
(a|ab)(bc([de]+)f|cde) abcdef 0 6
a([bc]?)c abc 0 3
a([bc]?)c ac 0 2
a([bc]+)c abc 0 3
a([bc]+)c abcc 0 4
a([bc]+)bc abcbc 0 5
a(bb+|b)b abb 0 3
a(bbb+|bb+|b)b abb 0 3
a(bbb+|bb+|b)b abbb 0 4
a(bbb+|bb+|b)bb abbb 0 4
(.*).* abcdef 0 6
(a*)* bc 0 0

- normal nosubs REG_NO_POSIX_TEST
a(b?c)+d accd 0 4 
(wee|week)(knights|night) weeknights 0 10 
.* abc 0 3
a(b|(c))d abd 0 3 
a(b|(c))d acd 0 3
a(b*|c|e)d abbd 0 4
a(b*|c|e)d acd 0 3 
a(b*|c|e)d ad 0 2
a(b?)c abc 0 3
a(b?)c ac 0 2
a(b+)c abc 0 3
a(b+)c abbbc 0 5
a(b*)c ac 0 2
(a|ab)(bc([de]+)f|cde) abcdef 0 6
a([bc]?)c abc 0 3
a([bc]?)c ac 0 2
a([bc]+)c abc 0 3
a([bc]+)c abcc 0 4
a([bc]+)bc abcbc 0 5
a(bb+|b)b abb 0 3
a(bbb+|bb+|b)b abb 0 3
a(bbb+|bb+|b)b abbb 0 4
a(bbb+|bb+|b)bb abbb 0 4
(.*).* abcdef 0 6
(a*)* bc 0 0

#endif
}
