
#ifndef BOOST_REGEX_TEST_DEPRECATED
#define BOOST_REGEX_TEST_DEPRECATED

template <class charT, class Tag>
void test_deprecated(const charT&, const Tag&)
{
   // do nothing
}

void test_deprecated(const char&, const test_regex_search_tag&);
void test_deprecated(const wchar_t&, const test_regex_search_tag&);
void test_deprecated(const char&, const test_invalid_regex_tag&);
void test_deprecated(const wchar_t&, const test_invalid_regex_tag&);


#endif

