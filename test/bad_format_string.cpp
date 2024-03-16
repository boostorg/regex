/*
 *
 * Copyright (c) 2024
 * John Maddock
 *
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#include <iostream>
#include <boost/regex.hpp>
#include <boost/core/lightweight_test.hpp>

int main()
{
   try{
      std::string format_string("(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((");
      boost::regex e("foo");
      std::string in("foobar");
      std::string out;
      boost::regex_replace(std::back_inserter(out), in.begin(), in.end(),
         e, format_string, boost::match_default | boost::format_all);
      BOOST_TEST(false);
   }
   catch (const std::runtime_error&)
   {
      std::cout << "OK" << std::endl;
   }
   return boost::report_errors();
}
