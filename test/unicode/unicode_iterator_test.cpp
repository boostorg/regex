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
  *   FILE         unicode_iterator_test.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Simple test suite for Unicode interconversions.
  */

#include <boost/regex/pending/unicode_iterator.hpp>
#include <boost/test/included/test_exec_monitor.hpp>
#include <vector>
#include <iterator>
#include <algorithm>

void spot_checks()
{
   // test specific values ripped straight out of the Unicode standard
   // to verify that our encoding is the same as theirs, as well as 
   // self-consistent:
   ::boost::uint32_t spot16[] = { 0x10302u, };
   typedef boost::u32_to_u16_iterator<const ::boost::uint32_t*> u32to16type;

   u32to16type it(spot16);
   BOOST_CHECK_EQUAL(*it++, 0xD800u);
   BOOST_CHECK_EQUAL(*it++, 0xDF02u);
   BOOST_CHECK_EQUAL(*--it, 0xDF02u);
   BOOST_CHECK_EQUAL(*--it, 0xD800u);

}

void test(const std::vector< ::boost::uint32_t>& v)
{
   typedef std::vector< ::boost::uint32_t> vector32_type;
   typedef std::vector< ::boost::uint16_t> vector16_type;
   typedef boost::u32_to_u16_iterator<vector32_type::const_iterator, ::boost::uint16_t> u32to16type;
   typedef boost::u16_to_u32_iterator<vector16_type::const_iterator, ::boost::uint32_t> u16to32type;
   typedef std::reverse_iterator<u32to16type> ru32to16type;
   typedef std::reverse_iterator<u16to32type> ru16to32type;
   vector16_type v16;
   vector32_type v32;
   vector32_type::const_iterator i, j, k;
   //
   // begin by testing forward iteration, of 32-16 bit interconversions:
   //
   v16.assign(u32to16type(v.begin()), u32to16type(v.end()));
   BOOST_CHECK_EQUAL(std::distance(u32to16type(v.begin()), u32to16type(v.end())), v16.size());
   v32.assign(u16to32type(v16.begin()), u16to32type(v16.end()));
   BOOST_CHECK_EQUAL(std::distance(u16to32type(v16.begin()), u16to32type(v16.end())), v32.size());
   BOOST_CHECK_EQUAL(v.size(), v32.size());
   i = v.begin();
   j = i;
   std::advance(j, (std::min)(v.size(), v32.size()));
   k = v32.begin();
   BOOST_CHECK_EQUAL_COLLECTIONS(
      i, 
      j, 
      k);
   //
   // test backward iteration, of 32-16 bit interconversions:
   //
   v16.assign(ru32to16type(u32to16type(v.end())), ru32to16type(u32to16type(v.begin())));
   BOOST_CHECK_EQUAL(std::distance(ru32to16type(u32to16type(v.end())), ru32to16type(u32to16type(v.begin()))), v16.size());
   std::reverse(v16.begin(), v16.end());
   v32.assign(ru16to32type(u16to32type(v16.end())), ru16to32type(u16to32type(v16.begin())));
   BOOST_CHECK_EQUAL(std::distance(ru16to32type(u16to32type(v16.end())), ru16to32type(u16to32type(v16.begin()))), v32.size());
   BOOST_CHECK_EQUAL(v.size(), v32.size());
   std::reverse(v32.begin(), v32.end());
   i = v.begin();
   j = i;
   std::advance(j, (std::min)(v.size(), v32.size()));
   k = v32.begin();
   BOOST_CHECK_EQUAL_COLLECTIONS(
      i, 
      j, 
      k);
}

int test_main( int, char* [] ) 
{
   // test specific value points from the standard:
   spot_checks();
   // now test a bunch of values for self-consistency and round-tripping:
   std::vector< ::boost::uint32_t> v;
   // start with boundary conditions:
   v.push_back(0);
   v.push_back(0xD7FF);
   v.push_back(0xE000);
   v.push_back(0xFFFF);
   v.push_back(0x10000);
   v.push_back(0x10FFFF);
   test(v);
   return 0;
}

