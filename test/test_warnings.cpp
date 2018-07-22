#ifdef _MSC_VER
#pragma warning(disable:4820 4668)
#endif

#include <boost/regex.hpp>

void test_proc()
{
   std::string text, re;
   boost::regex exp(re);
   regex_match(text, exp);
}