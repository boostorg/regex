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
  *   FILE         icu.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Unicode regular expressions on top of the ICU Library.
  */

#include <boost/regex/icu.hpp>

namespace boost{

namespace re_detail{

icu_regex_traits_implementation::string_type icu_regex_traits_implementation::do_transform(const char_type* p1, const char_type* p2, const ::Collator* pcoll) const
{
   // TODO make thread safe!!!! :
   typedef u32_to_u16_iterator<const char_type*, ::UChar> itt;
   itt i(p1), j(p2);
   std::vector< ::UChar> t(i, j);
   ::uint8_t result[100];
   ::int32_t len = pcoll->getSortKey(&*t.begin(), static_cast< ::int32_t>(t.size()), result, sizeof(result));
   if(len > sizeof(result))
   {
      scoped_array< ::uint8_t> presult(new ::uint8_t[len+1]);
      len = pcoll->getSortKey(&*t.begin(), static_cast< ::int32_t>(t.size()), presult.get(), len+1);
      if(0 == presult[len-1])
         --len;
      return string_type(presult.get(), presult.get()+len);
   }
   if(0 == result[len-1])
      --len;
   return string_type(result, result+len);
}

}

icu_regex_traits::size_type icu_regex_traits::length(const char_type* p)
{
   size_type result = 0;
   while(*p)
   {
      ++p;
      ++result;
   }
   return result;
}

//
// define our bitmasks:
//
const icu_regex_traits::char_class_type icu_regex_traits::mask_blank = icu_regex_traits::char_class_type(1) << offset_blank;
const icu_regex_traits::char_class_type icu_regex_traits::mask_space = icu_regex_traits::char_class_type(1) << offset_space;
const icu_regex_traits::char_class_type icu_regex_traits::mask_xdigit = icu_regex_traits::char_class_type(1) << offset_xdigit;
const icu_regex_traits::char_class_type icu_regex_traits::mask_underscore = icu_regex_traits::char_class_type(1) << offset_underscore;
const icu_regex_traits::char_class_type icu_regex_traits::mask_unicode = icu_regex_traits::char_class_type(1) << offset_unicode;

icu_regex_traits::char_class_type icu_regex_traits::lookup_classname(const char_type* p1, const char_type* p2) const
{
   static const char_class_type masks[] = 
   {
      0,
      U_GC_L_MASK | U_GC_ND_MASK, 
      U_GC_L_MASK,
      mask_blank,
      U_GC_CC_MASK | U_GC_CF_MASK | U_GC_ZL_MASK | U_GC_ZP_MASK,
      U_GC_ND_MASK,
      U_GC_ND_MASK,
      (0x3FFFFFFFu) & ~(U_GC_CC_MASK | U_GC_CF_MASK | U_GC_CS_MASK | U_GC_CN_MASK | U_GC_Z_MASK),
      U_GC_LL_MASK,
      U_GC_LL_MASK,
      ~(U_GC_C_MASK),
      U_GC_P_MASK,
      char_class_type(U_GC_Z_MASK) | mask_space,
      char_class_type(U_GC_Z_MASK) | mask_space,
      U_GC_LU_MASK,
      mask_unicode,
      U_GC_LU_MASK,
      char_class_type(U_GC_L_MASK | U_GC_ND_MASK) | mask_underscore, 
      char_class_type(U_GC_L_MASK | U_GC_ND_MASK) | mask_underscore, 
      char_class_type(U_GC_ND_MASK) | mask_xdigit,
   };

   int id = ::boost::re_detail::get_default_class_id(p1, p2);
   if(id < 0)
   {
      string_type s(p1, p2);
      for(string_type::size_type i = 0; i < s.size(); ++i)
         s[i] = static_cast<char>((::u_tolower)(s[i]));
      id = ::boost::re_detail::get_default_class_id(&*s.begin(), &*s.begin() + s.size());
   }
   BOOST_ASSERT(id+1 < sizeof(masks) / sizeof(masks[0]));
   return masks[id+1];
}

icu_regex_traits::string_type icu_regex_traits::lookup_collatename(const char_type* p1, const char_type* p2) const
{
   string_type result;
   if(std::find_if(p1, p2, std::bind2nd(std::greater< ::UChar32>(), 0x7f)) == p2)
   {
      std::string s(p1, p2);
      s = ::boost::re_detail::lookup_default_collate_name(s);
      result.assign(s.begin(), s.end());
   }
   if(result.empty() && (p2-p1 == 1))
      result.push_back(*p1);
   return result;
}

bool icu_regex_traits::isctype(char_type c, char_class_type f) const
{
   // check for standard catagories first:
   char_class_type m = char_class_type(1u << u_charType(c));
   if((m & f).any()) 
      return true;
   // now check for special cases:
   if((f & mask_blank).any() && u_isblank(c))
      return true;
   if((f & mask_space).any() && u_isspace(c))
      return true;
   if((f & mask_xdigit).any() && (u_digit(c, 16) >= 0))
      return true;
   if((f & mask_unicode).any() && (c >= 0x100))
      return true;
   if((f & mask_underscore).any() && (c == '_'))
      return true;
   return false;
}

}

