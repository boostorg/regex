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
  *   FILE         test_icu.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Test code for Unicode regexes with ICU support.
  */

//
// We can only build this if we have ICU support:
//
#include <boost/regex/config.hpp>
#ifdef BOOST_HAS_ICU

#include <boost/regex/icu.hpp>
#include "test.hpp"


void test_icu(const wchar_t&, const test_regex_search_tag& )
{
   boost::u32regex r;
   if(*test_locale::c_str())
   {
      ::Locale l(test_locale::c_str());
      if(l.isBogus())
         return;
      r.imbue(l);
   }

   std::vector< ::UChar32> expression;
   expression.assign(test_info<wchar_t>::expression().begin(), test_info<wchar_t>::expression().end());
   boost::regex_constants::syntax_option_type syntax_options = test_info<UChar32>::syntax_options();
   try{
      r.assign(expression.begin(), expression.end(), syntax_options);
      if(r.status())
      {
         BOOST_REGEX_TEST_ERROR("Expression did not compile when it should have done, error code = " << r.status(), UChar32);
      }
      std::vector< ::UChar32> search_text;
      search_text.assign(test_info<wchar_t>::search_text().begin(), test_info<wchar_t>::search_text().end());
      boost::regex_constants::match_flag_type opts = test_info<wchar_t>::match_options();
      const int* answer_table = test_info<wchar_t>::answer_table();
      boost::match_results<std::vector< ::UChar32>::const_iterator> what;
      if(boost::regex_search(
         const_cast<std::vector< ::UChar32>const&>(search_text).begin(),
         const_cast<std::vector< ::UChar32>const&>(search_text).end(),
         what,
         r,
         opts))
      {
         test_result(what, const_cast<std::vector< ::UChar32>const&>(search_text).begin(), answer_table);
      }
      else if(answer_table[0] >= 0)
      {
         // we should have had a match but didn't:
         BOOST_REGEX_TEST_ERROR("Expected match was not found.", UChar32);
      }
   }
   catch(const boost::bad_expression& e)
   {
      BOOST_REGEX_TEST_ERROR("Expression did not compile when it should have done: " << e.what(), UChar32);
   }
   catch(const std::runtime_error& r)
   {
      BOOST_REGEX_TEST_ERROR("Received an unexpected std::runtime_error: " << r.what(), UChar32);
   }
   catch(const std::exception& r)
   {
      BOOST_REGEX_TEST_ERROR("Received an unexpected std::exception: " << r.what(), UChar32);
   }
   catch(...)
   {
      BOOST_REGEX_TEST_ERROR("Received an unexpected exception of unknown type", UChar32);
   }
}

void test_icu(const wchar_t&, const test_invalid_regex_tag&)
{
   typedef boost::u16_to_u32_iterator<std::wstring::const_iterator, ::UChar32> conv_iterator;
   std::vector< ::UChar32> expression;
   expression.assign(test_info<wchar_t>::expression().begin(), test_info<wchar_t>::expression().end());
   boost::regex_constants::syntax_option_type syntax_options = test_info<wchar_t>::syntax_options();
   boost::u32regex r;
   if(*test_locale::c_str())
   {
      ::Locale l(test_locale::c_str());
      if(l.isBogus())
         return;
      r.imbue(l);
   }
   //
   // try it with exceptions disabled first:
   //
   try
   {
      if(0 == r.assign(expression.begin(), expression.end(), syntax_options | boost::regex_constants::no_except).status())
      {
         BOOST_REGEX_TEST_ERROR("Expression compiled when it should not have done so.", wchar_t);
      }
   }
   catch(...)
   {
      BOOST_REGEX_TEST_ERROR("Unexpected exception thrown.", wchar_t);
   }
   //
   // now try again with exceptions:
   //
   bool have_catch = false;
   try{
      r.assign(expression.begin(), expression.end(), syntax_options);
#ifdef BOOST_NO_EXCEPTIONS
      if(r.status())
         have_catch = true;
#endif
   }
   catch(const boost::bad_expression&)
   {
      have_catch = true;
   }
   catch(const std::runtime_error& r)
   {
      have_catch = true;
      BOOST_REGEX_TEST_ERROR("Expected a bad_expression exception, but a std::runtime_error instead: " << r.what(), wchar_t);
   }
   catch(const std::exception& r)
   {
      have_catch = true;
      BOOST_REGEX_TEST_ERROR("Expected a bad_expression exception, but a std::exception instead: " << r.what(), wchar_t);
   }
   catch(...)
   {
      have_catch = true;
      BOOST_REGEX_TEST_ERROR("Expected a bad_expression exception, but got an exception of unknown type instead", wchar_t);
   }
   if(!have_catch)
   {
      // oops expected exception was not thrown:
      BOOST_REGEX_TEST_ERROR("Expected an exception, but didn't find one.", wchar_t);
   }
}

void test_icu(const wchar_t&, const test_regex_replace_tag&)
{
   std::vector< ::UChar32> expression;
   expression.assign(test_info<wchar_t>::expression().begin(), test_info<wchar_t>::expression().end());
   boost::regex_constants::syntax_option_type syntax_options = test_info<UChar32>::syntax_options();
   boost::u32regex r;
   try{
      r.assign(expression.begin(), expression.end(), syntax_options);
      if(r.status())
      {
         BOOST_REGEX_TEST_ERROR("Expression did not compile when it should have done, error code = " << r.status(), UChar32);
      }
      typedef std::vector<UChar32> string_type;
      string_type search_text;
      search_text.assign(test_info<UChar32>::search_text().begin(), test_info<UChar32>::search_text().end());
      boost::regex_constants::match_flag_type opts = test_info<UChar32>::match_options();
      string_type format_string;
      format_string.assign(test_info<UChar32>::format_string().begin(), test_info<UChar32>::format_string().end());
      format_string.push_back(0);
      string_type result_string;
      result_string.assign(test_info<UChar32>::result_string().begin(), test_info<UChar32>::result_string().end());
      string_type result;

      boost::regex_replace(std::back_inserter(result), search_text.begin(), search_text.end(), r, &*format_string.begin(), opts);
      if(result != result_string)
      {
         BOOST_REGEX_TEST_ERROR("regex_replace generated an incorrect string result", UChar32);
      }
   }
   catch(const boost::bad_expression& e)
   {
      BOOST_REGEX_TEST_ERROR("Expression did not compile when it should have done: " << e.what(), UChar32);
   }
   catch(const std::runtime_error& r)
   {
      BOOST_REGEX_TEST_ERROR("Received an unexpected std::runtime_error: " << r.what(), UChar32);
   }
   catch(const std::exception& r)
   {
      BOOST_REGEX_TEST_ERROR("Received an unexpected std::exception: " << r.what(), UChar32);
   }
   catch(...)
   {
      BOOST_REGEX_TEST_ERROR("Received an unexpected exception of unknown type", UChar32);
   }
}

#else

#include "test.hpp"

void test_icu(const wchar_t&, const test_regex_search_tag&){}
void test_icu(const wchar_t&, const test_invalid_regex_tag&){}
void test_icu(const wchar_t&, const test_regex_replace_tag&){}

#endif
