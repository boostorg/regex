
#ifndef BOOST_REGEX_REGRESS_REGEX_SEARCH_HPP
#define BOOST_REGEX_REGRESS_REGEX_SEARCH_HPP
#include "info.hpp"
//
// this file implements a test for a regular expression that should compile,
// followed by a search for that expression:
//
struct test_regex_search_tag{};

template <class BidirectionalIterator>
void test_sub_match(const boost::sub_match<BidirectionalIterator>& sub, BidirectionalIterator base, const int* answer_table, int i)
{
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4244)
#endif
   typedef typename boost::sub_match<BidirectionalIterator>::value_type charT;
   if(sub.matched == 0)
   {
      if(answer_table[2*i] >= 0)
      {
         BOOST_REGEX_TEST_ERROR(
            "Sub-expression " << i 
            << " was not matched when it should have been.", charT);
      }
   }
   else
   {
      if(std::distance(base, sub.first) != answer_table[2*i])
      {
         BOOST_REGEX_TEST_ERROR(
            "Error in start location of sub-expression " 
            << i << ", found " << std::distance(base, sub.first) 
            << ", expected " << answer_table[2*i] << ".", charT);
      }
      if(std::distance(base, sub.second) != answer_table[1+ 2*i])
      {
         BOOST_REGEX_TEST_ERROR(
            "Error in end location of sub-expression " 
            << i << ", found " << std::distance(base, sub.second) 
            << ", expected " << answer_table[1 + 2*i] << ".", charT);
      }
   }
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
}

template <class BidirectionalIterator, class Allocator>
void test_result(const boost::match_results<BidirectionalIterator, Allocator>& what, BidirectionalIterator base, const int* answer_table)
{
   for(unsigned i = 0; i < what.size(); ++i)
   {
      test_sub_match(what[i], base, answer_table, i);
   }
}

template<class charT, class traits>
void test_simple_search(boost::basic_regex<charT, traits>& r)
{
   typedef typename std::basic_string<charT>::const_iterator const_iterator;
   const std::basic_string<charT>& search_text = test_info<charT>::search_text();
   boost::regex_constants::match_flag_type opts = test_info<charT>::match_options();
   const int* answer_table = test_info<charT>::answer_table();
   boost::match_results<const_iterator> what;
   if(boost::regex_search(
      search_text.begin(),
      search_text.end(),
      what,
      r,
      opts))
   {
      test_result(what, search_text.begin(), answer_table);
   }
   else if(answer_table[0] >= 0)
   {
      // we should have had a match but didn't:
      BOOST_REGEX_TEST_ERROR("Expected match was not found.", charT);
   }
}

template<class charT, class traits>
void test(boost::basic_regex<charT, traits>& r, const test_regex_search_tag&)
{
   const std::basic_string<charT>& expression = test_info<charT>::expression();
   boost::regex_constants::syntax_option_type syntax_options = test_info<charT>::syntax_options();
   try{
      r.assign(expression, syntax_options);
      test_simple_search(r);
   }
   catch(const boost::bad_expression& e)
   {
      BOOST_REGEX_TEST_ERROR("Expression did not compile when it should have done: " << e.what(), charT);
   }
   catch(const std::runtime_error& r)
   {
      BOOST_REGEX_TEST_ERROR("Received an unexpected std::runtime_error: " << r.what(), charT);
   }
   catch(const std::exception& r)
   {
      BOOST_REGEX_TEST_ERROR("Received an unexpected std::exception: " << r.what(), charT);
   }
   catch(...)
   {
      BOOST_REGEX_TEST_ERROR("Received an unexpected exception of unknown type", charT);
   }

}



#endif
