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

#include "test.hpp"
#include <clocale>
#ifndef BOOST_DISABLE_WIN32
#include <windows.h>
#endif

test_locale::test_locale(const char* c_name, boost::uint32_t lcid)
{
   // back up C locale and then set it's new name:
   m_old_c_locale = std::setlocale(LC_ALL, 0);
   m_old_c_state = s_c_locale;
   if(std::setlocale(LC_ALL, c_name))
   {
      s_c_locale = test_with_locale;
   }
   else
      s_c_locale = no_test;

   // back up the C++ locale and create the new one:
   m_old_cpp_locale = s_cpp_locale_inst;
   m_old_cpp_state = s_cpp_locale;
   try{
      s_cpp_locale_inst = std::locale(c_name);
      s_cpp_locale = test_with_locale;
   }catch(std::runtime_error const &)
   {
      s_cpp_locale = no_test;
   }

   // back up win locale and create the new one:
   m_old_win_locale = s_win_locale_inst;
   m_old_win_state = s_win_locale;
   s_win_locale_inst = lcid;
   if(::IsValidLocale(lcid, LCID_INSTALLED))
      s_win_locale = test_with_locale;
   else
      s_win_locale = no_test;
}

test_locale::~test_locale()
{
   // restore to previous state:
   std::setlocale(LC_ALL, m_old_c_locale.c_str());
   s_c_locale = m_old_c_state;
   s_cpp_locale_inst = m_old_cpp_locale;
   s_cpp_locale = m_old_cpp_state;
   s_win_locale_inst = m_old_win_locale;
   s_win_locale = m_old_win_state;
}

int test_locale::s_c_locale = test_no_locale;
int test_locale::s_cpp_locale = test_no_locale;
int test_locale::s_win_locale = test_no_locale;
std::locale test_locale::s_cpp_locale_inst;
boost::uint32_t test_locale::s_win_locale_inst = 0;


void test_en_locale(const char* name, boost::uint32_t lcid)
{
   using namespace boost::regex_constants;
   errors_as_warnings w;
   test_locale l(name, lcid);
   TEST_REGEX_SEARCH("[[:lower:]]+", perl, "Şßàáâãäåæçèéêëìíîïğñòóôõöøùúûüış÷", match_default, make_array(1, 32, -2, -2));
   TEST_REGEX_SEARCH("[[:upper:]]+", perl, "¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖØÙÚÛÜİŞß", match_default, make_array(1, 31, -2, -2));
   TEST_REGEX_SEARCH("[[:punct:]]+", perl, "¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿À", match_default, make_array(0, 31, -2, -2));
   TEST_REGEX_SEARCH("[[:print:]]+", perl, "¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäåæçèéêëìíîïğñòóôõö÷øùúûüış", match_default, make_array(0, 94, -2, -2));
   TEST_REGEX_SEARCH("[[:graph:]]+", perl, "¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäåæçèéêëìíîïğñòóôõö÷øùúûüış", match_default, make_array(0, 94, -2, -2));
   TEST_REGEX_SEARCH("[[:word:]]+", perl, "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖØÙÚÛÜİŞßàáâãäåæçèéêëìíîïğñòóôõöøùúûüış", match_default, make_array(0, 61, -2, -2));
   // collation sensitive ranges:
#if !BOOST_WORKAROUND(__BORLANDC__, < 0x600)
   // these tests are disabled for Borland C++: a bug in std::collate<wchar_t>
   // causes these tests to crash (pointer overrun in std::collate<wchar_t>::do_transform).
   TEST_REGEX_SEARCH("[a-z]+", perl|collate, "ßàáâãäåçèéêëìíîïğñòóôõöøùúûü", match_default, make_array(0, 28, -2, -2));
   TEST_REGEX_SEARCH("[a-z]+", perl|collate, "¿ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖØÙÚÛÜ", match_default, make_array(1, 28, -2, -2));
   // and equivalence classes:
   TEST_REGEX_SEARCH("[[=a=]]+", perl, "aAàáâãäåÀÁÂÃÄÅ", match_default, make_array(0, 14, -2, -2));
   // case mapping:
   TEST_REGEX_SEARCH("[A-Z]+", perl|icase|collate, "ßàáâãäåçèéêëìíîïğñòóôõöøùúûü", match_default, make_array(0, 28, -2, -2));
   TEST_REGEX_SEARCH("[a-z]+", perl|icase|collate, "¿ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖØÙÚÛÜ", match_default, make_array(1, 28, -2, -2));
   TEST_REGEX_SEARCH("ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖØÙÚÛÜİ", perl|icase, "ßàáâãäåæçèéêëìíîïğñòóôõöøùúûüış", match_default, make_array(1, 30, -2, -2));
#endif
}

void test_en_locale()
{
   test_en_locale("en_US", 0x09 | 0x01 << 10);
   test_en_locale("en_UK", 0x09 | 0x02 << 10);
   test_en_locale("en", 0x09);
}

