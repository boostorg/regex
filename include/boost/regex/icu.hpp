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
  *   FILE         icu.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Unicode regular expressions on top of the ICU Library.
  */

#ifndef BOOST_REGEX_ICU_HPP
#define BOOST_REGEX_ICU_HPP

#include <unicode/utypes.h>
#include <unicode/uchar.h>
#include <unicode/coll.h>
#include <boost/regex.hpp>
#include <boost/regex/pending/unicode_iterator.hpp>
#include <bitset>

namespace boost{

namespace re_detail{

// 
// Implementation details:
//
class icu_regex_traits_implementation
{
   typedef UChar32                      char_type;
   typedef std::size_t                  size_type;
   typedef std::vector<char_type>       string_type;
   typedef ::Locale                     locale_type;
   typedef boost::uint_least32_t        char_class_type;
public:
   icu_regex_traits_implementation(const ::Locale& l)
      : m_locale(l)
   {
      UErrorCode success = U_ZERO_ERROR;
      m_collator.reset( ::Collator::createInstance(l, success));
      if(U_SUCCESS(success) == 0)
         init_error();
      m_collator->setStrength(::Collator::IDENTICAL);
      success = U_ZERO_ERROR;
      m_primary_collator.reset( ::Collator::createInstance(l, success));
      if(U_SUCCESS(success) == 0)
         init_error();
      m_primary_collator->setStrength(::Collator::PRIMARY);
   }
   ::Locale getloc()const
   {
      return m_locale;
   }
   string_type do_transform(const char_type* p1, const char_type* p2, const ::Collator* pcoll) const;
   string_type transform(const char_type* p1, const char_type* p2) const
   {
      return do_transform(p1, p2, m_collator.get());
   }
   string_type transform_primary(const char_type* p1, const char_type* p2) const
   {
      return do_transform(p1, p2, m_primary_collator.get());
   }
private:
   void init_error()
   {
      std::runtime_error e("Could not initialize ICU resources");
      boost::throw_exception(e);
   }
   ::Locale m_locale;                                  // The ICU locale that we're using
   boost::scoped_ptr< ::Collator> m_collator;          // The full collation object
   boost::scoped_ptr< ::Collator> m_primary_collator;  // The primary collation object
};

inline boost::shared_ptr<icu_regex_traits_implementation> get_icu_regex_traits_implementation(const ::Locale& loc)
{
   return boost::shared_ptr<icu_regex_traits_implementation>(new icu_regex_traits_implementation(loc));
}

}

class icu_regex_traits
{
public:
   typedef UChar32                      char_type;
   typedef std::size_t                  size_type;
   typedef std::vector<char_type>       string_type;
   typedef ::Locale                     locale_type;
   typedef std::bitset<64>              char_class_type;

   struct boost_extensions_tag{};

   icu_regex_traits()
      : m_pimpl(re_detail::get_icu_regex_traits_implementation(::Locale()))
   {
   }
   static size_type length(const char_type* p);

   ::boost::regex_constants::syntax_type syntax_type(char_type c)const
   {
      return ((c < 0x7f) && (c > 0)) ? re_detail::get_default_syntax_type(static_cast<char>(c)) : regex_constants::syntax_char;
   }
   ::boost::regex_constants::escape_syntax_type escape_syntax_type(char_type c) const
   {
      return ((c < 0x7f) && (c > 0)) ? re_detail::get_default_escape_syntax_type(static_cast<char>(c)) : regex_constants::syntax_char;
   }
   char_type translate(char_type c) const
   {
      return c;
   }
   char_type translate_nocase(char_type c) const
   {
      return ::u_tolower(c);
   }
   char_type translate(char_type c, bool icase) const
   {
      return icase ? translate_nocase(c) : translate(c);
   }
   char_type tolower(char_type c) const
   {
      return ::u_tolower(c);
   }
   char_type toupper(char_type c) const
   {
      return ::u_toupper(c);
   }
   string_type transform(const char_type* p1, const char_type* p2) const
   {
      return m_pimpl->transform(p1, p2);
   }
   string_type transform_primary(const char_type* p1, const char_type* p2) const
   {
      return m_pimpl->transform_primary(p1, p2);
   }
   char_class_type lookup_classname(const char_type* p1, const char_type* p2) const;
   string_type lookup_collatename(const char_type* p1, const char_type* p2) const;
   bool isctype(char_type c, char_class_type f) const;
   int toi(const char_type*& p1, const char_type* p2, int radix)const
   {
      return re_detail::global_toi(p1, p2, radix, *this);
   }
   int value(char_type c, int radix)const
   {
      return u_digit(c, static_cast< ::int8_t>(radix));
   }
   locale_type imbue(locale_type l)
   {
      locale_type result(m_pimpl->getloc());
      m_pimpl = re_detail::get_icu_regex_traits_implementation(l);
      return result;
   }
   locale_type getloc()const
   {
      return locale_type();
   }
   std::string error_string(::boost::regex_constants::error_type n) const
   {
      return re_detail::get_default_error_string(n);
   }
private:
   icu_regex_traits(const icu_regex_traits&);
   icu_regex_traits& operator=(const icu_regex_traits&);

   //
   // define the bitmasks offsets we need for additional character properties:
   //
   enum{
      offset_blank = U_CHAR_CATEGORY_COUNT,
      offset_space = U_CHAR_CATEGORY_COUNT+1,
      offset_xdigit = U_CHAR_CATEGORY_COUNT+2,
      offset_underscore = U_CHAR_CATEGORY_COUNT+3,
      offset_unicode = U_CHAR_CATEGORY_COUNT+4,
   };

   //
   // and now the masks:
   //
   static const char_class_type mask_blank;
   static const char_class_type mask_space;
   static const char_class_type mask_xdigit;
   static const char_class_type mask_underscore;
   static const char_class_type mask_unicode;

   boost::shared_ptr< ::boost::re_detail::icu_regex_traits_implementation> m_pimpl;
};

// types:
typedef basic_regex< ::UChar32, icu_regex_traits> u32regex;
typedef match_results<const ::UChar32*> u32match;

} // namespace boost.

#endif
